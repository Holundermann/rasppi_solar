/*
 * Session.cpp
 *
 *  Created on: Sep 29, 2012
 *      Author: clemens
 */

#include "Session.h"

#include <boost/bind.hpp>
#include <vector>
#include "string.h"

Session::Session(boost::asio::io_service& io, Interpreter* interpreter, Parser* parser) :
                 socket_(io),
                 interpreter_(interpreter),
                 parser_(parser)
{}

Session::~Session()
{}


void Session::start()
{
  socket_.async_read_some(boost::asio::buffer(data_, max_length),
      boost::bind(&Session::handle_read, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Session::handle_read(const boost::system::error_code& e,
                          size_t bytes_transferred)
{
  if(!e)
  {
    interpreter_->setSession(this);
    string tmp(data_);
    size_t pos = tmp.find('\r',1);
    if(pos == string::npos)
      tmp.append("\r");
    parser_->setDevices(interpreter_->getDevices());
    vector<string> tmp_vec = parser_->getParams(tmp);
    vector<Token*> tokens = parser_->getTokens(tmp_vec, interpreter_->getCommandsMap());

    if (tmp.compare(0,4,"exit"))
    {
      if(!interpreter_->execute(tokens.begin(), tokens.end()) && tmp.compare("\n"))
        feedback_ = "couldn´t execute command: " + tmp;
      std::clog << "tmp is: " << tmp << " Feedback is: " << feedback_ << std::endl;
      for(int i = 0; data_[i] != '\0'; i++)
        data_[i] = '\0';
      feedback_ += '\n';
      boost::asio::async_write(socket_, boost::asio::buffer(feedback_),
                               boost::bind(&Session::handle_write, this,
                               boost::asio::placeholders::error));
      feedback_.clear();
    }
    else
      delete this;
  }
  else
    delete this;
}

void Session::handle_write(const boost::system::error_code& e)
{
  if(!e)
  {
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
                            boost::bind(&Session::handle_read, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
  }
  else
    delete this;
}

void Session::setFeedback(std::string fb)
{
  feedback_ = fb;
}
