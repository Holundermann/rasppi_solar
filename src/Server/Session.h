/*
 * Session.h
 *
 *  Created on: Sep 29, 2012
 *      Author: clemens
 */

#ifndef SESSION_H_
#define SESSION_H_

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <string>

#include "../Interpreter.h"
#include "../Parser.h"

using boost::asio::ip::tcp;

class Session
{
  private:
    tcp::socket socket_;
    std::string feedback_;
    Interpreter* interpreter_;
    Parser* parser_;
    enum { max_length = 1024 };
    char data_[max_length];
//    std::string data_;
    void handle_read(const boost::system::error_code& e,
                       size_t bytes_transferred);
    void handle_write(const boost::system::error_code& e);


  public:
    Session(boost::asio::io_service& io, Interpreter* interpreter, Parser* parser);
    virtual ~Session();

    void start();
    void setFeedback(std::string fb);
    tcp::socket& getSocket() {return socket_;};
};

#endif /* SESSION_H_ */
