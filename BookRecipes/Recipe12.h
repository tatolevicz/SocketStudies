//
// Created by Arthur Motelevicz on 22/02/23.
//

#ifndef SOCKET_RECIPE12_H
#define SOCKET_RECIPE12_H

#include <boost/asio.hpp>

class Recipe12 {
public:
    struct Session;
    static int execute();
    static void writeToSocketAsync(std::shared_ptr<boost::asio::ip::tcp::socket> sock, const std::string& message);
    static void writeCB(const boost::system::error_code& ec, std::size_t bytes_transferred);
    static void callAsyncWrite(const std::shared_ptr<Session>& s);
};

#endif //SOCKET_RECIPE12_H
