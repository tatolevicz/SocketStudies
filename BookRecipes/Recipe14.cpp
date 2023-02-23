//
// Created by Arthur Motelevicz on 22/02/23.
//

#include "Recipe14.h"
#include <iostream>
#include "Common.h"

using namespace boost;

void Recipe14::onConnect(const boost::system::error_code& ec, const std::shared_ptr<boost::asio::ip::tcp::socket>& sock) {
    if (ec.value() == asio::error::operation_aborted) {
        std::cout << "Operation cancelled\n";
        return ;
    } else {
        CHECK_ERROR_VOID(ec)
    }
}

//CANCELING OPERATIONS - Pag 84
int Recipe14::execute() {
    try {
        //solve host
        std::string host = "localhost";
        std::string port = "1234";

        asio::ip::tcp::resolver::query q(host, port, asio::ip::tcp::resolver::numeric_service);
        asio::io_context ioc;
        asio::ip::tcp::resolver resolver(ioc);


        std::shared_ptr<asio::ip::tcp::socket> sock(new asio::ip::tcp::socket(ioc));

        //async connect using bing
//        system::error_code ec;
//        auto endpoints = resolver.resolve(q,ec);
//        CHECK_ERROR(ec)
//        asio::async_connect(*sock,endpoints, std::bind(onConnect, std::placeholders::_1, sock));

        //or this option with lambda function

        asio::async_connect(*sock, resolver.resolve(q),
       [sock](const boost::system::error_code& error, const tcp::endpoint& endpoint) {
           if (!error) {
               std::cout << "Connected to " << endpoint << std::endl;
           } else {
               std::cout << "Error: " << error.message() << std::endl;
           }
       });

        std::thread worker([&ioc]() {
            try {
                ioc.run();
            }
            catch (system::system_error &e) {
                std::cout << "Error occurred: " << "Error code: " << e.code() << " Message: " << e.what() << "\n";
            }
        });

        std::this_thread::sleep_for(std::chrono::seconds(1));

        sock->cancel();

        worker.join();
    }
    catch (system::system_error &e) {
        std::cout << "Error occurred: " << "Error code: " << e.code() << " Message: " << e.what() << "\n";
        return e.code().value();
    }

    return 0;

}