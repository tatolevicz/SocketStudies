//
// Created by Arthur Motelevicz on 21/02/23.
//

#include "Recipe9.h"
#include <iostream>
#include "Common.h"

using namespace boost;

//Recipe 9 -> Writing synchronously
// Page 50 ~=  kindle book: Boost.Asio c++ programing
void Recipe9::writeToSocket(boost::asio::ip::tcp::socket& sock, const std::string& message){
    std::size_t totalBytesWritten = 0;
    while(totalBytesWritten < message.length()){
        auto output_buffer =  asio::buffer(message.c_str() + totalBytesWritten, message.length() - totalBytesWritten);
        totalBytesWritten += sock.write_some(output_buffer);
    }

    return;
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
            writeToSocket(sock, "Oi gatão!!!\n");
        }
    }
    catch(system::system_error& e){
        std::cerr << "Error occurred: " << e.code() << " Message: " << e.what() <<"\n";
    }


    return 0;

}
