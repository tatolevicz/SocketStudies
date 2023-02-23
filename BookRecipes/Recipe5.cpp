//
// Created by Arthur Motelevicz on 20/02/23.
//

#include "Recipe5.h"
#include <boost/asio.hpp>
#include <iostream>
#include "Common.h"

using namespace boost;

//Recipe14 5 -> BIDING ENDPOINT TO SOCKET - ACCEPTOR (SERVER)
// Position 779 kindle book: Boost.Asio c++ programing
int Recipe5::execute(){

    unsigned short port_num = 3333;

    asio::ip::address ip_address = asio::ip::address_v4::any();

    asio::ip::tcp::endpoint ep(ip_address, port_num);

    asio::io_service ios;

    asio::ip::tcp::acceptor sock(ios, ep.protocol());

    system::error_code ec;

    sock.bind(ep,ec);

    CHECK_ERROR(ec)

    return 0;
}
