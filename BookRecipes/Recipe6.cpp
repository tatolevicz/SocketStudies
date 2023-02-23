//
// Created by Arthur Motelevicz on 20/02/23.
//

#include "Recipe6.h"
#include <boost/asio.hpp>
#include <iostream>
#include "Common.h"

using namespace boost;

//Recipe14 5 -> CONNECTING A SOCKET
// Position 821 kindle book: Boost.Asio c++ programing

int Recipe6::execute(){

    std::string host = "localhost";
    std::string port_num = "1234";

    asio::io_context ios;

    asio::ip::tcp::resolver::query resolver_query(host,port_num,asio::ip::tcp::resolver::numeric_service);

    asio::ip::tcp::resolver resolver(ios);
    system::error_code ec;

    asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query, ec);
    CHECK_ERROR(ec)

    asio::ip::tcp::socket sock(ios);

    asio::connect(sock,it,ec);
    CHECK_ERROR(ec)

    return 0;
}