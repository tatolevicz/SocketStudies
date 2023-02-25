//
// Created by Arthur Motelevicz on 25/02/23.
//

#ifndef SOCKET_SERVERTESTS_H
#define SOCKET_SERVERTESTS_H

#include "Common.h"

class ServerTests {
public:
    static void readAsync(boost::asio::ip::tcp::socket& sock);
    static void readCB(const boost::system::error_code& ec,
                       const std::size_t bytes_read,
                       boost::asio::ip::tcp::socket* sock,
                       char* buf);

    static void readCB_2(const boost::system::error_code& ec,
                       const std::size_t bytes_read,
                       boost::asio::ip::tcp::socket* sock);
    static int execute();

    static void print_bytes(const char* buffer, size_t size);

};


#endif //SOCKET_SERVERTESTS_H
