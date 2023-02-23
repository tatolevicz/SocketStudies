//
// Created by Arthur Motelevicz on 22/02/23.
//

#include "Recipe15.h"
#include <iostream>
#include "Common.h"

using namespace boost;
//CLIENT SIDE - SHUT DOWN MESSAGE - Pag 84

void Recipe15::communicate(boost::asio::ip::tcp::socket &sock){
    const char request_buf[] = {'o','l','a','\n'};//{0x38, 0x65, 0x0, 0x0c, 0x6c, 0x6f};
    asio::write(sock, asio::buffer(request_buf));
    sock.shutdown(asio::socket_base::shutdown_send);

    asio::streambuf responseBuf;

    system::error_code ec;
    asio::read(sock,responseBuf,ec);
    if(ec == asio::error::eof){
        // Get the remaining data in the buffer as a string
        std::string response_data(boost::asio::buffers_begin(responseBuf.data()),
                                  boost::asio::buffers_end(responseBuf.data()));

        std::cout << "Response data: " << response_data << std::endl;
        std::cout << "Message EOF!\n";
    }
    else{
        throw system::system_error(ec);
    }
}


int Recipe15::execute() {
    std::string host = "localhost";
    std::string port = "1234";

    asio::ip::tcp::resolver::query q(host,port,asio::ip::tcp::resolver::numeric_service);

    asio::io_context ioc;
    asio::ip::tcp::socket sock(ioc);
    asio::ip::tcp::resolver resolver(ioc);

    try {
        asio::async_connect(
        sock,
        resolver.resolve(q),
        [&](const system::error_code &ec, const asio::ip::tcp::endpoint &ep) {
            CHECK_ERROR_VOID(ec)
            communicate(sock);
        });

        ioc.run();
    }
    catch (boost::system::system_error& e){
        std::cerr << "Error:  " << e.what() << "\n";
        return e.code().value();
    }

    return 0;
}






