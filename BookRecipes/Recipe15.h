//
// Created by Arthur Motelevicz on 22/02/23.
//

#ifndef SOCKET_RECIPE15_H
#define SOCKET_RECIPE15_H

#include <boost/asio.hpp>
class Recipe15 {
public:
    static void communicate(boost::asio::ip::tcp::socket &sock);
    static int execute();
};


#endif //SOCKET_RECIPE15_H
