//
// Created by Arthur Motelevicz on 25/02/23.
//

#ifndef SOCKET_SERVERTESTS_H
#define SOCKET_SERVERTESTS_H

#include "Common.h"

class ServerTests {
public:


    static void readAsync(boost::asio::ip::tcp::socket& sock);
    static void readHeaderAsync(boost::asio::ip::tcp::socket& sock);
    static void writeAcceptHeaderAsync(boost::asio::ip::tcp::socket& sock, const std::string& responseHeader);
    static void readHeaderCB(const boost::system::error_code& ec,
                       const std::size_t bytes_read,
                       boost::asio::ip::tcp::socket* sock);
    static void readCB_2(const boost::system::error_code& ec,
                       const std::size_t bytes_read,
                       boost::asio::ip::tcp::socket* sock,
                       const char* buf);
    static int execute();


};


#endif //SOCKET_SERVERTESTS_H
