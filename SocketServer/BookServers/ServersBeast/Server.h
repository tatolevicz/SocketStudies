//
// Created by Arthur Motelevicz on 26/02/23.
//

#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>

//server beast
namespace sb {
    class ServerState;
    class Doorman;

    class Server : public std::enable_shared_from_this<Server> {
    public:
        Server(std::shared_ptr<ServerState> sharedState);
        void start();
        void stop();

    private:
        std::shared_ptr<ServerState> _serverState{nullptr};
        std::shared_ptr<Doorman> _doorMan{nullptr};

    };

}


#endif //SOCKET_SERVER_H
