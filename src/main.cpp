/*
 *  main.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: clemens
 */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#include <string.h>
#include <iostream>
#include <fstream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "curl/curl.h"

#include "Filter.h"
#include "Parser.h"
#include "Controller.h"
#include "Server/Server.h"

#define LOGFILE "./rasppi_solar.log"
#define LOOPTIME 300

using namespace std;

const string URL = "http://pvserver:pvwr@192.168.0.100/index.fhtml";
//const char* URL = "localhost:8020";

void daemonize()
{
  pid_t pid, sid;
  // Fork of the parent process
  pid = fork();
  if (pid < 0) exit(EXIT_FAILURE);
  // If we got a good PID, then we can exit the parent process,
  // child process keeps on running
  if (pid > 0) exit(EXIT_SUCCESS);
  // mask for newly created files
  umask(0);
  // set new unique session id
  sid = setsid();
  if (sid < 0) exit(EXIT_FAILURE);
  if (chdir("/") < 0) exit(EXIT_FAILURE);
}

bool getPage(Filter& f)
{
  CURL *curl_handle;

  curl_global_init(CURL_GLOBAL_ALL);
  /* init the curl session */
  curl_handle = curl_easy_init();
  /* set URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, URL.c_str());
  /* no progress meter please */
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, &Filter::handle);

  /*
   * Notice here that if you want the actual data sent anywhere else but
   * stdout, you should consider using the CURLOPT_WRITEDATA option.  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &f);
  /* get it! */
  CURLcode result = curl_easy_perform(curl_handle);
  /* cleanup curl stuff */

  curl_easy_reset(curl_handle);
  curl_easy_cleanup(curl_handle);

  if (result == CURLE_OK) return true;
  return false;
}

static string getTime()
{
  time_t rawtime;
  time(&rawtime);
  string time = asctime(localtime(&rawtime));
  time.erase(time.end() - 1);
  return time;
}

void execute(const boost::system::error_code& /*e*/,
    boost::asio::deadline_timer* t, Controller* controller, Parser* parser,
    int* aktuell_prev)
{
  Filter filter;
  int aktuell, gesamt = 0;

  if (getPage(filter))
  {
    parser->setContent(filter.getContent());
    aktuell = parser->getAktuell();
    gesamt = parser->getGesamt();
  }
  else
  {
    cerr << getTime() << ": coulnd´t fetch page" << endl;
    if (*aktuell_prev >= 100)
      aktuell = *aktuell_prev - 100;
    else if (*aktuell_prev >= 10)
      aktuell = *aktuell_prev - 10;
    else if (*aktuell_prev > 0)
      aktuell = *aktuell_prev - 1;
  }

  controller->setAktuell(aktuell);
  if (aktuell != *aktuell_prev)
    clog << getTime() << ": Aktuelle Leistung: " << aktuell
        << " W Gesamtenergie: " << gesamt << " W" << endl;
  filter.resetContent();
  controller->run();
  *aktuell_prev = aktuell;
//  sleep(LOOPTIME);
  t->expires_at(t->expires_at() + boost::posix_time::seconds(LOOPTIME));
  t->async_wait(
      boost::bind(execute, boost::asio::placeholders::error, t, controller,
          parser, aktuell_prev));
}

int main(void)
{
  ofstream outfile(LOGFILE);
  Controller controller;
  Parser parser;
  Interpreter interpreter(controller.getDevices());

  int aktuell_prev = -1;
  boost::asio::io_service io;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(0));

  t.async_wait(
      boost::bind(execute, boost::asio::placeholders::error, &t, &controller,
          &parser, &aktuell_prev));

  Server server(io, 5220, &interpreter, &parser);

  cerr.rdbuf(outfile.rdbuf());
  clog.rdbuf(outfile.rdbuf());

//  daemonize();

  try
  {
    io.run();
  }
  catch (std::exception &e)
  {
    std::cerr << "an critical error occurred, in - " << e.what()
        << "program terminating" << std::endl;
    outfile.close();
    exit(EXIT_FAILURE);
  }

  return 0;
}
