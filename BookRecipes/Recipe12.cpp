//
// Created by Arthur Motelevicz on 22/02/23.
//

#include "Recipe12.h"

#include <iostream>
#include "Common.h"

using namespace boost;

struct Recipe12::Session{
    std::shared_ptr<asio::ip::tcp::socket> sock;
    std::string buff;
};

//WRITE SOME ASYNC IMPROVED- Pag 69
int Recipe12::execute() {

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
    std::shared_ptr<asio::ip::tcp::socket> sock( new asio::ip::tcp::socket(ioc));
    asio::connect(*sock.get(),endpoints,ec);
    CHECK_ERROR(ec)

    writeToSocketAsync(sock, "Minha menssagem nova!\n");
    ioc.run();

    return 0;
}

void Recipe12::writeCB(const system::error_code& ec, std::size_t bytes_transferred){
    CHECK_ERROR_VOID(ec)
    std::cout << "Bytes sent: " << bytes_transferred << "\n";
}


void Recipe12::writeToSocketAsync(std::shared_ptr<boost::asio::ip::tcp::socket> sock, const std::string& message){

    std::shared_ptr<Session> s(new Session);
    s->buff = message;
    s->sock = sock;

    callAsyncWrite(s);
}

void Recipe12::callAsyncWrite(const std::shared_ptr<Session>& s){

    asio::async_write(  *s->sock.get(),
                        asio::buffer(s->buff),
                        std::bind(writeCB,std::placeholders::_1, std::placeholders::_2));
}