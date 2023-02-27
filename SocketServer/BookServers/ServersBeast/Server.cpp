//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "Server.h"
#include "ServerState.h"
#include "Doorman.h"


//server beast
namespace sb {

Server::Server(){

}

void Server::start(){
    _endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(),1234);
    _serverState = std::make_shared<ServerState>();
    _doorMan = std::make_shared<Doorman>(_ioc, _endpoint, _serverState);
    _doorMan->run();
    _ioc.run();
}

void Server::stop(){

}

}
