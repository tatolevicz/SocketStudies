//
// Created by Arthur Motelevicz on 22/02/23.
//

#ifndef SOCKET_RECIPE13_H
#define SOCKET_RECIPE13_H


#include <boost/asio.hpp>

class Recipe13 {
public:
    static int execute();
    static void readFromSocketAsync(std::shared_ptr<boost::asio::ip::tcp::socket> sock);
    static void readCB(const boost::system::error_code& ec, std::size_t bytes_transferred,std::shared_ptr<boost::asio::ip::tcp::socket> sock, char* buf);
};
#endif //SOCKET_RECIPE13_H
