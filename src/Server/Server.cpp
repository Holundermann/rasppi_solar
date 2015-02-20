/*
 * Server.cpp
 *
 *  Created on: Sep 29, 2012
 *      Author: clemens
 */

#include "Server.h"
#include <boost/bind.hpp>

Server::Server(boost::asio::io_service& io, short port, Interpreter* interpreter,
                                                         Parser* parser) :
        io_(io),
        acceptor_(io,tcp::endpoint(tcp::v4(), port))
{
  interpreter_ = interpreter;
  parser_ = parser;
  start_accept();
}

Server::~Server()
{
  delete interpreter_;
}

void Server::start_accept()
{
  Session* new_session = new Session(io_, interpreter_, parser_);
  acceptor_.async_accept(new_session->getSocket(),
                         boost::bind(&Server::handle_accept, this, new_session,
                         boost::asio::placeholders::error));
}

void Server::handle_accept(Session* new_session,
                           const boost::system::error_code& e)
{
  if(!e)
  {
    new_session->start();
  }
  else
    delete new_session;

  start_accept();
}

