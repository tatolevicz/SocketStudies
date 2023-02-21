//
// Created by Arthur Motelevicz on 21/02/23.
//

#ifndef SOCKET_RECIPE9_H
#define SOCKET_RECIPE9_H

#include <boost/asio.hpp>

class Recipe9 {
public:
    static void writeToSocket(boost::asio::ip::tcp::socket& sock, const std::string& message);
    static int execute();
};


#endif //SOCKET_RECIPE9_H
