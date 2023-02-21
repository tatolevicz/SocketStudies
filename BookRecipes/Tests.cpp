//
// Created by Arthur Motelevicz on 20/02/23.
//

#include "Tests.h"
#include <boost/asio.hpp>
#include <iostream>
#include "Common.h"

using namespace boost;

//TESTING EVERYTHING TOGETHER

int Tests::execute(){

    //RESOLVING HOST
    std::string host = "localhost";
    std::string port_num = "1234";

    asio::io_context ios;

    asio::ip::tcp::resolver::query resolver_query(host,port_num,asio::ip::tcp::resolver::numeric_service);

    asio::ip::tcp::resolver resolver(ios);
    system::error_code ec;

    asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query, ec);
    CHECK_ERROR(ec)

    //CONNECTING SOCKET TO BEST ENDPOINT AVAILABLE
    asio::ip::tcp::socket sock(ios);
    asio::connect(sock,it,ec);
    CHECK_ERROR(ec)

    //SEND A TEST MESSAGE TO THE HOST
    const std::string message = "Hello world!\n";
    asio::const_buffers_1 output_buf = asio::buffer(message);
    sock.send(output_buf);



    return 0;
}