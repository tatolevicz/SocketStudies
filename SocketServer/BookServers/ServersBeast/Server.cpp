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

    // Capture SIGINT and SIGTERM to perform a clean shutdown
    boost::asio::signal_set signals(_ioc, SIGINT, SIGTERM);
    signals.async_wait(
    [&](boost::system::error_code const&, int)
    {
        disconnectAll();
        _doorMan->stop();
        // Stop the io_context. This will cause run()
        // to return immediately, eventually destroying the
        // io_context and any remaining handlers in it.
        _ioc.stop();
    });
}

void Server::disconnectAll() {
    _serverState->leaveAll();
}

}
