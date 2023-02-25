//
// Created by Arthur Motelevicz on 25/02/23.
//

#include "ServerTests.h"
#include "Common.h"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/algorithm/string.hpp>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <iostream>
#include <string>
#include "AsyncHandShake.h"
using namespace boost;

void ServerTests::readAsync(boost::asio::ip::tcp::socket& sock){

    const std::size_t READ_SIZE = 1;
    char* buf = new char[READ_SIZE];
    asio::mutable_buffers_1 inputBuffer = asio::buffer(buf, READ_SIZE);
    asio::async_read(sock, inputBuffer, std::bind(readCB_2, std::placeholders::_1, std::placeholders::_2, &sock, buf));
}


void ServerTests::readCB_2(const boost::system::error_code& ec,
                         const std::size_t bytes_read,
                         boost::asio::ip::tcp::socket* sock,
                         const char* buf){

    CHECK_ERROR_VOID(ec)

    for(int i = 0; i < bytes_read; i++)
        std::cout <<buf[i];


    readAsync(*sock);
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

    //run read async in a thread and write async in another
//    readHeaderAsync(sock);
    auto asyncHandShake = AsyncHandShake(sock, [](const system::error_code&  ec){
        std::cout << "\n\nOnHandShake completed: " << ec.value() << "\n\n";
    });

    asyncHandShake.execute();

    ioc.run();

    return 0;
}




//
//int main() {
//    std::string request = "GET / HTTP/1.1\r\n"
//                          "Sec-WebSocket-Key: EuXJlXBmGmDUtOoYFamVtA==\r\n"
//                          "Connection: Upgrade\r\n"
//                          "Upgrade: websocket\r\n"
//                          "Sec-WebSocket-Extensions: permessage-deflate; client_max_window_bits\r\n"
//                          "Host: localhost:1234\r\n\r\n";
//
//    handle_websocket_request(request);
//    return 0;
//}
