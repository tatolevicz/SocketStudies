//
// Created by Arthur Motelevicz on 20/02/23.
//

#include "Recipe1.h"
#include <boost/asio.hpp>
#include <iostream>
#include "Common.h"

using namespace boost;

//Recipe 1 -> CREATING ENDPOINTS
// Position 436 kindle book: Boost.Asio c++ programing
int Recipe1::executeClient(){

    std::string raw_ip_address = "192.168.1.234";
    unsigned short port_num = 3333;

    system::error_code ec;
    asio::ip::address ip_adress = asio::ip::address::from_string(raw_ip_address, ec);

    CHECK_ERROR(ec)

    asio::ip::tcp::endpoint ep(ip_adress, port_num);

    return 0;
}

int Recipe1::executeServer(){
    unsigned short port_num = 3333;

    system::error_code ec;
    asio::ip::address ip_adress = asio::ip::address_v6::any();

    asio::ip::tcp::endpoint ep(ip_adress, port_num);

    return 0;
}