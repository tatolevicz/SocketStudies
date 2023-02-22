//
// Created by Arthur Motelevicz on 21/02/23.
//

#include "Recipe11.h"

#include <iostream>
#include "Common.h"

using namespace boost;

//WRITE SOME ASYNC- Pag 63
int Recipe11::execute() {

    //solve host
    std::string host = "localhost";
    std::string port = "1234";

    asio::ip::tcp::resolver::query q(host, port, asio::ip::tcp::resolver::numeric_service);
    asio::io_context ioc;
    asio::ip::tcp::resolver resolver(ioc);

    system::error_code ec;
    auto endpoints = resolver.resolve(q,ec);
    CHECK_ERROR(ec)

    //creat open connect socket
    asio::ip::tcp::socket sock(ioc);
    asio::connect(sock,endpoints,ec);
    CHECK_ERROR(ec)

    //create output buffer
    const std::string message = "Esta aqui é minha mensagem pra você!\n";
    asio::const_buffers_1 outputBuffer = asio::buffer(message);

    auto writeCB = [&](const system::error_code& ec, std::size_t bytes_transferred){
        CHECK_ERROR(ec)
        std::cout << "Wrote: " << bytes_transferred << " Bytes" << "\n";
    };

    sock.async_write_some(outputBuffer,writeCB);
    ioc.run();


    return 0;
}

