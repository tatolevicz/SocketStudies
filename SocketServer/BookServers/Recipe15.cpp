//
// Created by Arthur Motelevicz on 22/02/23.
//

#include "Recipe15.h"
#include <iostream>
#include "Common.h"

using namespace boost;
 //SERVER SIDE - SHUT DOWN MESSAGE - Pag 84v


void Recipe15::processRequest(boost::asio::ip::tcp::socket& sock){

    asio::streambuf request_buf;
    system::error_code ec;
    asio::read(sock, request_buf,ec);

    std::string requestData(asio::buffers_begin(request_buf.data()),
                            asio::buffers_end(request_buf.data()));

    std::cout << "Client message:  "<< requestData << "\n";

    if(ec != asio::error::eof)
        throw system::system_error(ec);

    const char response_buf[] = {'M','e','s','s','a','g','e',' ','r','e','a','d','!'};

    asio::write(sock, asio::buffer(response_buf));

    sock.shutdown(asio::socket_base::shutdown_send);
}


int Recipe15::execute() {
    unsigned short port = 1234;
    try{
        asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(),port);
        asio::io_context ioc;
        asio::ip::tcp::acceptor acceptor(ioc,ep);
        asio::ip::tcp::socket sock(ioc);
        acceptor.accept(sock);
        processRequest(sock);
    }
    catch(boost::system::system_error& e){
        std::cout << "Error :" << e.what() << "\n";
        return e.code().value();
    }

    return 0;
}
