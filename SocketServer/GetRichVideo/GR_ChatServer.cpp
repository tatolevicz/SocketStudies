//
// Created by Arthur Motelevicz on 25/02/23.
//

#include "GR_ChatServer.h"
#include "GRCommon.h"
#include "Listener.h"
#include "SharedState.h"

namespace gr_video {
    int GR_ChatServer::execute() {
        auto address = net::ip::make_address("127.0.0.1");
        auto port = static_cast<unsigned short>(std::atoi("1234"));
        std::string docRoot = "";

        net::io_context ioc;

        std::make_shared<Listener>(
                ioc,
                tcp::endpoint{address, port},
                std::make_shared<SharedState(docRoot)>
        );

        ioc.run();

        return EXIT_SUCCESS;
    }
}