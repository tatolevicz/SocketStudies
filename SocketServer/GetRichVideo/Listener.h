//
// Created by Arthur Motelevicz on 25/02/23.
//

#ifndef SOCKET_LISTENER_H
#define SOCKET_LISTENER_H

#include "GRCommon.h"

namespace gr_video {

    //Accepts incoming connections
class Listener : public std::enable_shared_from_this<Listener>{
    tcp::acceptor _acceptor;
    tcp::socket _socket;
    std::shared_ptr<SharedState> _state{nullptr};

    void fail(error_code ec, char const* what);
    void onAccept(error_code ec);

public:
    Listener(
            net::io_context& ioc,
            tcp::endpoint endpoint,
            std::shared_ptr<SharedState> const& state);

    void run();
};

}

#endif //SOCKET_LISTENER_H
