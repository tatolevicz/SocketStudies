//
// Created by Arthur Motelevicz on 25/02/23.
//

#ifndef SOCKET_ASYNCHANDSHAKE_H
#define SOCKET_ASYNCHANDSHAKE_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <iostream>
#include <string>

class AsyncHandShake {
public:
    using OnHandShake = std::function<void(const boost::system::error_code& ec)>;
    AsyncHandShake(const std::shared_ptr<boost::asio::ip::tcp::socket>& soc, const OnHandShake cb = nullptr);

    void execute();

private:
  void readHeaderAsync(boost::asio::ip::tcp::socket* sock);
  void writeAcceptHeader(boost::asio::ip::tcp::socket* sock, const std::string& responseHeader);

  void readHeaderCB(    const boost::system::error_code& ec,
                        const std::size_t bytes_read,
                        boost::asio::ip::tcp::socket* sock);

    OnHandShake _cb {nullptr};

    std::string generate_websocket_accept_key(const std::string& websocket_key);
    std::string handle_websocket_request(const std::string& request);
    std::shared_ptr<std::string> _data;
    std::shared_ptr<boost::asio::ip::tcp::socket> _sock{nullptr};

//  int checkError(const boost::system::error_code& ec);
};


#endif //SOCKET_ASYNCHANDSHAKE_H
