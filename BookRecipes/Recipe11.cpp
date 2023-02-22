//
// Created by Arthur Motelevicz on 21/02/23.
//

#include "Recipe11.h"

#include <iostream>
#include "Common.h"

using namespace boost;

struct Recipe11::Session{
    std::shared_ptr<asio::ip::tcp::socket> sock;
    std::string buff;
    std::size_t total_bytes_written;
};

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
    std::shared_ptr<asio::ip::tcp::socket> sock( new asio::ip::tcp::socket(ioc));
    asio::connect(*sock.get(),endpoints,ec);
    CHECK_ERROR(ec)

    writeToSocketAsync(sock, "Minha menssagem nova!\n");
    ioc.run();

    return 0;
}

void Recipe11::writeCB(const system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Recipe11::Session> s){
    CHECK_ERROR_VOID(ec)

    s->total_bytes_written += bytes_transferred;
    if(s->total_bytes_written >= s->buff.length())
        return;

    callAsyncWrite(s);
}

void Recipe11::writeToSocketAsync(std::shared_ptr<boost::asio::ip::tcp::socket> sock, const std::string& message){

    std::shared_ptr<Session> s(new Session);
    s->buff = message;
    s->total_bytes_written = 0;
    s->sock = sock;

    callAsyncWrite(s);
}

void Recipe11::callAsyncWrite(const std::shared_ptr<Session>& s){
    s->sock->async_write_some(
            asio::buffer(s->buff.c_str() + s->total_bytes_written, s->buff.length() - s->total_bytes_written),
            std::bind(writeCB,std::placeholders::_1, std::placeholders::_2, s));
}