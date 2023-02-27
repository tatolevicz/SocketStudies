//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "ServerState.h"
#include "Client.h"
#include "WebsocketConnection.h"

//server beast
namespace sb {

ServerState::ServerState(){

}

std::shared_ptr<Client> ServerState::join(const std::shared_ptr<WebsocketConnection>& connection){
    auto client = std::make_shared<Client>(connection);
    _clients.push_back(client);
    return client;
}

void ServerState::leave(const std::shared_ptr<WebsocketConnection>& connection){
    auto it = std::find_if(_clients.begin(), _clients.end(),[&](std::shared_ptr<Client> &client){
        return client->getConnection() == connection;
    });

    if(it != _clients.end())
        _clients.erase(it);
    else
        std::cerr <<  "Nao achou o client pra deletar!\n\n";

}

void ServerState::send(const std::string& message){
    for(auto c: _clients)
        c->getConnection()->send(message);
}

}
