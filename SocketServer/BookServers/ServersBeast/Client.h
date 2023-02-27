//
// Created by Arthur Motelevicz on 26/02/23.
//

#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>

//server beast
namespace sb {
    class ServerState;
    class WebsocketConnection;

    class Client : public std::enable_shared_from_this<Client> {
    public:
        inline static unsigned long idCounter = 0;
        Client(WebsocketConnection* connection);
        unsigned long getId() const;
        WebsocketConnection* getConnection();
    private:
        WebsocketConnection* _connection{nullptr};
        unsigned long _id = 0;
    };

}


#endif //SOCKET_CLIENT_H


