//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "Doorman.h"
#include "ServerState.h"
#include <iostream>

//server beast
namespace sb {

Doorman::Doorman(boost::asio::io_context& ioc,
                 boost::asio::ip::tcp::endpoint& endpoint,
                 std::shared_ptr<ServerState> sharedState) :
        _sock(ioc),
        _acceptor(ioc),
        _serverState(std::move(sharedState)){

    boost::system::error_code ec;

    // Open the acceptor
    _acceptor.open(endpoint.protocol(), ec);
    if(ec)
        return;


    // Allow address reuse
    _acceptor.set_option(boost::asio::socket_base::reuse_address(true));

    if(ec)
        return;

    // Bind to the server address
    _acceptor.bind(endpoint, ec);

    if(ec)
        return;

    // Start listening for connections
    _acceptor.listen(boost::asio::socket_base::max_listen_connections, ec);
    if(ec)
        return;

}

void Doorman::run(){
    _acceptor.async_accept(_sock, [&](boost::system::error_code ec){
        if(ec.value() != 0) {
            //todo:: start http listener here
        }
        else{
            std::cerr << "Error: " << ec.value() << " Msg: " << ec.message() << "\n";
        }

        run();
    });
}

}
