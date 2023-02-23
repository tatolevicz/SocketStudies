//
// Created by Arthur Motelevicz on 20/02/23.
//

#include "Recipe2.h"

#include <boost/asio.hpp>
#include <iostream>
#include "Common.h"

using namespace boost;

//Recipe14 2 -> CREATING SOCKET
// Position 579 kindle book: Boost.Asio c++ programing
int Recipe2::execute(){

    asio::io_service ios;

    asio::ip::tcp protocol = asio::ip::tcp::v4();

    asio::ip::tcp::socket sock(ios);

    system::error_code ec;

    sock.open(protocol, ec);

    CHECK_ERROR(ec)

    return 0;
}
