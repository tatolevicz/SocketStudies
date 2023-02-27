//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "HttpListener.h"
#include "ServerState.h"
#include "WebsocketConnection.h"

//server beast
namespace sb {

    HttpListener::HttpListener(std::shared_ptr<ServerState> state) :
            _serverState(std::move(state)) {

    }

}
