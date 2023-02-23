//
// Created by Arthur Motelevicz on 21/02/23.
//

#include "Recipe9.h"
#include <iostream>
#include "Common.h"

using namespace boost;

//Recipe14 9 -> Writing synchronously
// Page 50 ~=  kindle book: Boost.Asio c++ programing
void Recipe9::writeToSocket_1(boost::asio::ip::tcp::socket& sock, const std::string& message){
    std::size_t totalBytesWritten = 0;
    while(totalBytesWritten < message.length()){
        auto output_buffer =  asio::buffer(message.c_str() + totalBytesWritten, message.length() - totalBytesWritten);
        totalBytesWritten += sock.write_some(output_buffer);
        std::cout << "Bytes written: " << totalBytesWritten << "\n";
    }
}

void Recipe9::writeToSocket_2(boost::asio::ip::tcp::socket& sock, const std::string& message){
    auto output_buffer =  asio::buffer(message);
    asio::write(sock,output_buffer);
}

int Recipe9::execute() {

    std::string host = "localhost";
    std::string port_num = "1234";

    asio::io_context ioc;

    asio::ip::tcp::resolver::query resolver_query(host, port_num, asio::ip::tcp::resolver::numeric_service);

    asio::ip::tcp::resolver resolver(ioc);
    system::error_code ec;
    asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query,ec);
    CHECK_ERROR(ec)
    asio::ip::tcp::socket sock(ioc);

    asio::connect(sock, it, ec);
    CHECK_ERROR(ec)

    try{
        while(true) {
            std::string message = "";
            message += "There are many variations \n";
            writeToSocket_2(sock, message);
        }
    }
    catch(system::system_error& e){
        std::cerr << "Error occurred: " << e.code() << " Message: " << e.what() <<"\n";
    }

    return 0;
}
