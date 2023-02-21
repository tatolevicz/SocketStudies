//
// Created by Arthur Motelevicz on 21/02/23.
//

#ifndef SOCKET_TESTS_H
#define SOCKET_TESTS_H

#include <boost/asio.hpp>

class Tests {
public:
    static void writeToSocket(boost::asio::ip::tcp::socket& sock, const std::string& message);
    static int execute();
};


#endif //SOCKET_TESTS_H
