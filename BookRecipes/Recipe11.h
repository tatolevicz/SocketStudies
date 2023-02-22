//
// Created by Arthur Motelevicz on 21/02/23.
//

#ifndef SOCKET_RECIPE11_H
#define SOCKET_RECIPE11_H

#include <boost/asio.hpp>

class Recipe11 {
public:
    struct Session;
    static int execute();
    static void writeToSocketAsync(std::shared_ptr<boost::asio::ip::tcp::socket> sock, const std::string& message);
    static void writeCB(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session> s);
    static void callAsyncWrite(const std::shared_ptr<Session>& s);

    };
#endif //SOCKET_RECIPE11_H
