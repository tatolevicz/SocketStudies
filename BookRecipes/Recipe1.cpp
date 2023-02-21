//
// Created by Arthur Motelevicz on 20/02/23.
//

#include "Recipe1.h"
#include <boost/asio.hpp>
#include <iostream>


using namespace boost;

//Recipe 1 -> Position 436 kindle book: Boost.Asio c++ programing
int Recipe1::executeClient(){

    std::string raw_ip_address = "192.168.1.234";
    unsigned short port_num = 3333;

    system::error_code ec;
    asio::ip::address ip_adress = asio::ip::address::from_string(raw_ip_address, ec);

    if(ec.value() != 0){
        std::cerr << "Failed to parse ip address: " << ec.value() << " Message: " << ec.message() << "\n";
        return ec.value();
    }

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