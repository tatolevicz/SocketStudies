//
// Created by Arthur Motelevicz on 26/02/23.
//

#ifndef SOCKET_WEBSOCKETCONNECTION_H
#define SOCKET_WEBSOCKETCONNECTION_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>

//server beast
namespace sb {
    class ServerState;

    class WebsocketConnection : public std::enable_shared_from_this<WebsocketConnection> {
    public:
        WebsocketConnection(std::shared_ptr<ServerState> sharedState);

    private:
        std::shared_ptr<ServerState> _serverState{nullptr};

    };

}


#endif //SOCKET_WEBSOCKETCONNECTION_H
