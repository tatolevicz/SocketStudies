//
// Created by Arthur Motelevicz on 22/02/23.
//

#ifndef SOCKET_RECIPE14_H
#define SOCKET_RECIPE14_H


#include <boost/asio.hpp>
class Recipe14 {
public:
    static void onConnect(const boost::system::error_code& ec, const std::shared_ptr<boost::asio::ip::tcp::socket>& sock);
    static int execute();
};


#endif //SOCKET_RECIPE14_H
