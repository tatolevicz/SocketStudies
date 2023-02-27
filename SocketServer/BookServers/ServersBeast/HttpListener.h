//
// Created by Arthur Motelevicz on 26/02/23.
//

#ifndef SOCKET_HTTPLISTENER_H
#define SOCKET_HTTPLISTENER_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>

//server beast
namespace sb {
    class ServerState;

    class HttpListener : public std::enable_shared_from_this<HttpListener> {
    public:
        HttpListener(std::shared_ptr<ServerState> sharedState);

    private:
        std::shared_ptr<ServerState> _serverState{nullptr};

    };

}


#endif //SOCKET_HTTPLISTENER_H
