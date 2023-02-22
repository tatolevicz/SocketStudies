//
// Created by Arthur Motelevicz on 21/02/23.
//

#include "Recipe10.h"
#include <iostream>
#include "Common.h"
#include <boost/regex.hpp>

using namespace boost;

std::string Recipe10::readFromSocket_1(boost::asio::ip::tcp::socket& sock){
    unsigned int MSG_MAX_SIZE_BYTES = 1;
    std::unique_ptr<char[]> buf(new char[MSG_MAX_SIZE_BYTES]);

    size_t totalBytesWritten = 0;

    while(totalBytesWritten < MSG_MAX_SIZE_BYTES){
        asio::mutable_buffers_1 inputBuffer = asio::buffer(buf.get() + totalBytesWritten, MSG_MAX_SIZE_BYTES - totalBytesWritten);
//        totalBytesWritten += sock.receive(inputBuffer);
        totalBytesWritten += sock.read_some(inputBuffer);
    }

    std::string output = std::string(buf.get(),totalBytesWritten);
    return output;
}

std::string Recipe10::readFromSocket_2(boost::asio::ip::tcp::socket& sock){
    unsigned int MSG_MAX_SIZE_BYTES = 1;
    std::unique_ptr<char[]> buf(new char[MSG_MAX_SIZE_BYTES]);

    asio::mutable_buffers_1 inputBuffer = asio::buffer(buf.get(),MSG_MAX_SIZE_BYTES);
    asio::read(sock,inputBuffer);

    std::string output = std::string(buf.get(),MSG_MAX_SIZE_BYTES);
    return output;
}

//working badly with messages from mac terminal
std::string Recipe10::readFromSocket_3(boost::asio::ip::tcp::socket& sock){
    boost::asio::streambuf b;
    boost::asio::read_until(sock, b, 'A');
    std::istream is(&b);
    std::string line;
    std::getline(is, line,'A');
    return line;
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

   try {
       while (true) {
           auto message = readFromSocket_2(sock);
           if (!message.empty()) {
               std::cout << message;
               if (message == "q")
                   break;
           }
       }
   }
   catch(boost::system::system_error e){
       std::cerr << "Error throw: " << e.what() << "\n";
   }


    return 0;
}
