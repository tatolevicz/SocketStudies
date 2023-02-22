//
// Created by Arthur Motelevicz on 21/02/23.
//

#include "Recipe10.h"
#include <iostream>
#include "Common.h"

using namespace boost;

std::string Recipe10::readFromSocket(boost::asio::ip::tcp::socket& sock){
    unsigned int MSG_MAX_SIZE_BYTES = 1;
    std::unique_ptr<char[]> buf(new char[MSG_MAX_SIZE_BYTES]);

    size_t totalBytesWritten = 0;

    while(totalBytesWritten < MSG_MAX_SIZE_BYTES){
        asio::mutable_buffers_1 inputBuffer = asio::buffer(buf.get() + totalBytesWritten, MSG_MAX_SIZE_BYTES - totalBytesWritten);
        totalBytesWritten += sock.read_some(inputBuffer);
    }

    std::string output = std::string(buf.get(),totalBytesWritten);
    return output;
}

int Recipe10::execute() {

   std::string host = "localhost";
   std::string port = "1234";

   asio::ip::tcp::resolver::query query(host, port, asio::ip::tcp::resolver::numeric_service);

   asio::io_context ioc;

   asio::ip::tcp::resolver resolver(ioc);

   system::error_code ec;

   asio::ip::tcp::resolver::iterator it = resolver.resolve(query,ec);
   CHECK_ERROR(ec)

   asio::ip::tcp::socket sock(ioc);

   asio::connect(sock, it, ec);
   CHECK_ERROR(ec)

   while(true) {
       auto message = readFromSocket(sock);
       if(!message.empty()){
           std::cout << message ;
           if(message == "q")
               break;
       }
   }


    return 0;
}
