//
// Created by Arthur Motelevicz on 26/02/23.
//

#ifndef SOCKET_SERVERSTATE_H
#define SOCKET_SERVERSTATE_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>

//server beast
namespace sb {
    class ServerState;

    class ServerState : public std::enable_shared_from_this<ServerState> {
    public:
        ServerState();
    private:
    };

}


#endif //SOCKET_SERVERSTATE_H
