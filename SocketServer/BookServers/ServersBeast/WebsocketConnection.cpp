//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "WebsocketConnection.h"
#include "ServerState.h"

//server beast
namespace sb {

    WebsocketConnection::WebsocketConnection(std::shared_ptr<ServerState> state):
            _serverState(std::move(state)) {

    }

}
