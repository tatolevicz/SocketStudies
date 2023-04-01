//
// Created by Arthur Motelevicz on 26/02/23.
//

#ifndef SOCKET_SERVERSTATE_H
#define SOCKET_SERVERSTATE_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>

#define CHECK_ASIO_ERROR_(ec) \
    if(ec.value() != 0) { \
        std::cerr << "Error: " << ec.value() \
        << " at " << __FILE__ \
        << "(" << __LINE__ << ")"            \
        << " Message: " << ec.message() << "\n\n"; \
        return; \
    }


//server beast
namespace sb {
    class ServerState;
    class Client;
    class WebsocketConnection;

    class ServerState : public std::enable_shared_from_this<ServerState> {
    public:
        ServerState();
        std::shared_ptr<Client> join(WebsocketConnection* connection);
        void leave(WebsocketConnection* connection);
        void send(const std::string& message);
        void leaveAll();

    private:
        std::vector<std::shared_ptr<Client>> _clients;

    };

}


#endif //SOCKET_SERVERSTATE_H
