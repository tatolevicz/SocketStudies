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
        Server();
        void start();
        void stop();
        void disconnectAll();
    private:
        std::shared_ptr<ServerState> _serverState{nullptr};
        std::shared_ptr<Doorman> _doorMan{nullptr};

        boost::asio::io_context _ioc;
        boost::asio::ip::tcp::endpoint _endpoint;


    };

}


#endif //SOCKET_SERVER_H
