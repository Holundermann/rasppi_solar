/*
 * Server.h
 *
 *  Created on: Sep 29, 2012
 *      Author: clemens
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <boost/asio.hpp>

#include "Session.h"
#include "../Interpreter.h"
#include "../Parser.h"
#include "../Device.h"

using boost::asio::ip::tcp;

class Server
{
  private:
    Interpreter* interpreter_;
    Parser* parser_;

    boost::asio::io_service& io_;
    tcp::acceptor acceptor_;
    vector<Device*> devices_;

    void start_accept();
    void handle_accept(Session* new_session,
                       const boost::system::error_code& e);

  public:
    Server(boost::asio::io_service& io, short port, Interpreter* interpreter,
                                                      Parser* parser);
    virtual ~Server();
};

#endif /* SERVER_H_ */
