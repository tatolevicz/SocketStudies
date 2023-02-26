//
// Created by Arthur Motelevicz on 25/02/23.
//

#ifndef SOCKET_SHAREDSTATE_H
#define SOCKET_SHAREDSTATE_H

#include "GRCommon.h"

namespace gr_video {

    //Holds the server data
    class SharedState {
        std::string _docRoot;
        std::unordered_set<WebsocketSession*> _sessions;

    public:
        explicit SharedState(std::string doc_root);

        std::string const& docRoot() const noexcept{
            return _docRoot;
        }

        void join(WebsocketSession& session);
        void leave(WebsocketSession& session);
        void send(std::string message);
    };

}
#endif //SOCKET_SHAREDSTATE_H
