//
// Created by Arthur Motelevicz on 22/02/23.
//

#include "Recipe13.h"

#include <iostream>
#include "Common.h"

using namespace boost;

//WRITE SOME ASYNC IMPROVED- Pag 69
int Recipe13::execute() {

    //solve host
    std::string host = "localhost";
    std::string port = "1234";

    asio::ip::tcp::resolver::query q(host, port, asio::ip::tcp::resolver::numeric_service);
    asio::io_context ioc;
    asio::ip::tcp::resolver resolver(ioc);

    system::error_code ec;
    auto endpoints = resolver.resolve(q,ec);
    CHECK_ERROR(ec)

    //create open connect socket
    std::shared_ptr<asio::ip::tcp::socket> sock( new asio::ip::tcp::socket(ioc));
    asio::connect(*sock.get(),endpoints,ec);
    CHECK_ERROR(ec)

    readFromSocketAsync(sock);

    ioc.run();

    return 0;
}

void Recipe13::readCB(const system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<boost::asio::ip::tcp::socket> sock, char* buf){
    CHECK_ERROR_VOID(ec)
    std::cout << buf;
    readFromSocketAsync(sock);
    delete buf;
}


void Recipe13::readFromSocketAsync(std::shared_ptr<boost::asio::ip::tcp::socket> sock){
    std::size_t size_ = 1;
    char* buf = new char[size_];
    asio::mutable_buffers_1 out_buffer = asio::buffer(buf, size_);
    asio::async_read(*sock, out_buffer, std::bind(readCB,std::placeholders::_1, std::placeholders::_2, sock, buf));
}
