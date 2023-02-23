//
// Created by Arthur Motelevicz on 20/02/23.
//

#include "Recipe4.h"
#include <boost/asio.hpp>
#include <iostream>
#include "Common.h"

using namespace boost;

//Recipe14 4 -> RESOLVING DNS
// Position 650 kindle book: Boost.Asio c++ programing
int Recipe4::execute(){

    std::string host = "localhost";
    std::string port_num = "8080";

    asio::io_service ios;

    asio::ip::tcp::resolver::query resolver_query(host,port_num,asio::ip::tcp::resolver::numeric_service);

    asio::ip::tcp::resolver resolver(ios);
    system::error_code ec;

    //example how iterate the collection 1
    asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query, ec);
    CHECK_ERROR(ec)

    asio::ip::tcp::resolver::iterator it_end;

    for (; it != it_end; ++it) {
        std::cout << it->endpoint() << std::endl;
    }

    //example how iterate the collection 2
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(resolver_query,ec);
    CHECK_ERROR(ec)

    // Loop through the results and print out each endpoint
    for (auto endpoint_iterator = endpoints.begin(); endpoint_iterator != endpoints.end(); ++endpoint_iterator) {
        std::cout << endpoint_iterator->endpoint() << std::endl;
    }

    return 0;
}
