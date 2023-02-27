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

    class Client : public std::enable_shared_from_this<Client> {
    public:
        inline static unsigned long idCounter = 0;
        Client(std::shared_ptr<boost::asio::ip::tcp::socket> sock);
        unsigned long getId() const;
    private:
        std::shared_ptr<boost::asio::ip::tcp::socket> _sock{nullptr};
        unsigned long _id = 0;
    };

}


#endif //SOCKET_CLIENT_H


