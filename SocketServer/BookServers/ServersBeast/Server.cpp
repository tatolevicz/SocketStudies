//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "Server.h"
#include "ServerState.h"
#include "Doorman.h"


//server beast
namespace sb {

Server::Server(std::shared_ptr <ServerState> state) :
        _serverState(std::move(state)) {

}

void Server::start(){
//    _serverState = std::make_shared<>()
//    _doorMan
}

void Server::stop(){

}

}
