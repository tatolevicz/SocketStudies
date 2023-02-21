//
// Created by Arthur Motelevicz on 21/02/23.
//

#ifndef SOCKET_RECIPE10_H
#define SOCKET_RECIPE10_H


#include <boost/asio.hpp>

class Recipe10 {
public:
    static std::string readFromSocket(boost::asio::ip::tcp::socket& sock);
    static int execute();
};


#endif //SOCKET_RECIPE10_H
