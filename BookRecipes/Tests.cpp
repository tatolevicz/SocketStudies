//
// Created by Arthur Motelevicz on 20/02/23.
//

#include "Tests.h"
#include <boost/asio.hpp>
#include <iostream>
#include "Common.h"

using namespace boost;

//TESTING EVERYTHING TOGETHER

void Tests::writeToSocket(boost::asio::ip::tcp::socket& sock, const std::string& message){
    system::error_code ec;
    asio::write(sock,asio::buffer(message), ec);
    CHECK_ERROR_VOID(ec)
}

void Tests::readFromSocket(boost::asio::ip::tcp::socket& sock){
    system::error_code ec;
    std::size_t BYTES_SIZE = 1;
    std::shared_ptr<char[]> buf (new char[BYTES_SIZE]);
    asio::mutable_buffers_1 inputBuf = asio::buffer(buf.get(), BYTES_SIZE);

    asio::read(sock, inputBuf, ec);
    CHECK_ERROR_VOID(ec)

    std::cout << std::string(buf.get(), BYTES_SIZE);
}

void Tests::readCB(const boost::system::error_code& ec,
                   std::size_t bytes_transferred,
                   boost::asio::ip::tcp::socket* sock,
                   const char* buf){
    CHECK_ERROR_VOID(ec)
//    std::cout << "Read: " << bytes_transferred << " bytes\n";
    std::cout << std::string (buf, bytes_transferred);
    delete buf;
    readFromSocketAsync(sock);
}

void Tests::readFromSocketAsync(boost::asio::ip::tcp::socket* sock){
    std::size_t BYTES_SIZE = 1;
    char* buf = new char[BYTES_SIZE];
    asio::mutable_buffers_1 inputBuf = asio::buffer(buf, BYTES_SIZE);

    asio::async_read (*sock,
                      inputBuf,
                      std::bind(readCB, std::placeholders::_1, std::placeholders::_2, sock, buf));

}

int Tests::execute(){

    //host simple IP
//    std::string host = "127.0.0.1";
//    unsigned short port = 1234;
//    asio::ip::address ad = asio::ip::address::from_string(host);
//    asio::ip::tcp::endpoint ep = asio::ip::tcp::endpoint(ad, port);

    asio::io_context ioc;
    system::error_code ec;

    std::string host = "localhost";
    std::string port = "1234";

    asio::ip::tcp::resolver::query q(host, port, asio::ip::tcp::resolver::numeric_service);

    asio::ip::tcp::resolver resolver(ioc);

    asio::ip::tcp::resolver::results_type enpoints = resolver.resolve(q,ec);
    CHECK_ERROR(ec)


    asio::ip::tcp::socket sock(ioc);

    asio::connect(sock, enpoints, ec);
    CHECK_ERROR(ec)

    readFromSocketAsync(&sock);

    ioc.run();

    return 0;
}