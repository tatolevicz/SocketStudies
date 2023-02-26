//
// Created by Arthur Motelevicz on 25/02/23.
//

#include "SharedState.h"
#include "WebsocketSession.h"

namespace gr_video{

SharedState::SharedState(std::string doc_root) {

}

void SharedState::join(WebsocketSession& session){
    _sessions.insert(&session);
}

void SharedState::leave(WebsocketSession& session){
    _sessions.erase(&session);
}

void SharedState::send(std::string message){
    auto const ss = std::make_shared<std::string const>(std::move(message));
    for(auto s : _sessions){
        s->send(ss);
    }
}

}
