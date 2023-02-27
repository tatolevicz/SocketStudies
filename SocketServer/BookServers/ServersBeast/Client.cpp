//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "Client.h"
#include "ServerState.h"

//server beast
namespace sb {

Client::Client(std::shared_ptr<boost::asio::ip::tcp::socket> sock) :
_sock(std::move(sock))
{
    _id = ++idCounter;
}

unsigned long Client::getId() const {
    return _id;
}

}



