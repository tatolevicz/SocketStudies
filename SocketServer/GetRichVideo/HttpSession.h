//
// Created by Arthur Motelevicz on 25/02/23.
//

#ifndef SOCKET_HTTPSESSION_H
#define SOCKET_HTTPSESSION_H

#include "GRCommon.h"

namespace gr_video {

//Handles HTTP requests on a connection
class HttpSession : public std::enable_shared_from_this<HttpSession>{
    tcp::socket _socket;
    beast::flat_buffer _buffer;
    std::shared_ptr<SharedState> _state;
    http::request<http::string_body> _req;

    void fail(error_code ec, char const* what);
    void onRead(error_code ec, std::size_t size);
    void onWrite(error_code ec, std::size_t size, bool close);

public:
    HttpSession(tcp::socket socket,
                std::shared_ptr<SharedState> const& state);

    void run();
};
}

#endif //SOCKET_HTTPSESSION_H
