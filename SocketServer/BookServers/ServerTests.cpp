//
// Created by Arthur Motelevicz on 25/02/23.
//

#include "ServerTests.h"
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include "AsyncHandShake.h"
#include <iomanip>

using namespace boost;


std::shared_ptr<std::string> _data;

void ServerTests::readAsync(boost::asio::ip::tcp::socket& sock){

    const std::size_t READ_SIZE = 1;
    char* buf = new char[READ_SIZE];
    asio::mutable_buffers_1 inputBuffer = asio::buffer(buf, READ_SIZE);
    asio::async_read(sock, inputBuffer, std::bind(readCB, std::placeholders::_1, std::placeholders::_2, &sock, buf));

}

void ServerTests::readCB(const boost::system::error_code& ec,
                         const std::size_t bytes_read,
                         boost::asio::ip::tcp::socket* sock,
                         char* buf){

    CHECK_ERROR_VOID(ec)
    for(int i = 0; i < bytes_read; i++) {
        print_bytes(buf, 1);
    }

    delete buf;
    readAsync(*sock);
}

void ServerTests::print_bytes(const char* buffer, size_t size) {
    std::cout << "Bytes: ";
    for (size_t i = 0; i < size; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)buffer[i];
    }
    std::cout << std::endl;
}

int ServerTests::execute(){

    system::error_code ec;
    asio::io_context ioc;

    //enpoint
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(),1234);
    CHECK_ERROR(ec)

    //socket - to read the accepted connection
//    asio::ip::tcp::socket sock(ioc);
    std::shared_ptr<asio::ip::tcp::socket> sock(new asio::ip::tcp::socket(ioc));

    //acceptor accept
    asio::ip::tcp::acceptor acpt (ioc, ep);

    //wait for incomming clients
    acpt.accept(*sock,ec);
    CHECK_ERROR(ec)

    //use out OwnAsyncHandShake class
    /**
     * After handshake we keep a read loop but message received from postman (even though it is text ) only can be see it as bytes (maybe because it is the websocket protocol)
     */
    auto asyncHandShake = AsyncHandShake(sock, [&](const system::error_code&  ec){
        std::cout << "\n\nOnHandShake completed: " << ec.value() << "\n\n";
        readAsync(*sock);
    });


    asyncHandShake.execute();
    ioc.run();

    return 0;
}