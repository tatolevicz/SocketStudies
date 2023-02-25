//
// Created by Arthur Motelevicz on 23/02/23.
//

#include "BasicIntroduction.h"


/**
 * create a active socket to connect in a web site and read all the data
 * available until the end. When finished reading, finish the program.
 * */

#include "Common.h"

using namespace boost;

void BasicIntroduction::grabSomeData(asio::ip::tcp::socket& sock){

    char* buf = new char[BYTES_TO_READ];
    asio::mutable_buffers_1 inputBuf = asio::buffer(buf,BYTES_TO_READ);

    asio::async_read(sock,inputBuf,[&,buf](const system::error_code &ec, const std::size_t & bytes_transferred){

        std::cout << "\n\nBytes read: " << bytes_transferred << "\n\n";
        for(int i = 0; i < bytes_transferred; i++)
            std::cout << buf[i];

        if(ec != asio::error::eof) {
            CHECK_ERROR_VOID(ec)
        }


        grabSomeData(sock);
        CHECK_ERROR_VOID(ec);
    });

}

int BasicIntroduction::execute(){
    std::string host = "www.google.com";
    std::string port = "80";

    system::error_code ec;
    asio::ip::tcp::resolver::query q(host, port, asio::ip::tcp::resolver::numeric_service);
    asio::io_context ioc;

    asio::ip::tcp::socket sock(ioc);

    asio::ip::tcp::resolver resolver(ioc);

    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(q,ec);

    CHECK_ERROR(ec)

    asio::async_connect(sock,endpoints,[&](const system::error_code& ec, const asio::ip::tcp::endpoint& ep){
        if(ec.value() != 0){
            std::cerr << "Error : " << ec.message() << "\n";
            return;
        }

        std::cout << "Endppoint solved: " << ep.address() << "\n";
        if(sock.is_open()){
            // 1- write the http header to the host
            // 2- wait some data arrives
            // 3- grab all the data async

            //1
            std::string strRequest = "GET / HTTP/1.1\r\n"
                                    "Host: www.google.com\r\n"
                                    "Connection: close\r\n\r\n";

            sock.write_some(asio::buffer(strRequest,strRequest.size()));
                CHECK_ERROR_VOID(ec);

//            while(true) {
                //2
//                sock.wait(asio::socket_base::wait_read);
                //3
                grabSomeData(sock);
//            }
        }
    });

    ioc.run();

    return 0;
}