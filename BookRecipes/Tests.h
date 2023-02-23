//
// Created by Arthur Motelevicz on 21/02/23.
//

#ifndef SOCKET_TESTS_H
#define SOCKET_TESTS_H

#include <boost/asio.hpp>

class Tests {
public:
    static void writeToSocket(boost::asio::ip::tcp::socket& sock, const std::string& message);
    static void readFromSocket(boost::asio::ip::tcp::socket& sock);
    static void readFromSocketAsync(boost::asio::ip::tcp::socket* sock);
    static void readCB(const boost::system::error_code& ec,std::size_t bytes_transferred, boost::asio::ip::tcp::socket*sock, const char* buf);

    static int execute();
};

#endif //SOCKET_TESTS_H
