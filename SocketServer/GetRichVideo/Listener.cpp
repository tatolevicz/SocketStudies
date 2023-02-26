//
// Created by Arthur Motelevicz on 25/02/23.
//

#include "GRCommon.h"

#include "Listener.h"
#include "SharedState.h"
#include "HttpSession.h"

namespace gr_video{

Listener::Listener(net::io_context& ioc, tcp::endpoint endpoint, std::shared_ptr<SharedState> const& state):
_acceptor(ioc),
_socket(ioc),
_state(state)
{
    error_code ec;

    // Open the acceptor
    _acceptor.open(endpoint.protocol(), ec);
    if(ec)
    {
        fail(ec, "open");
        return;
    }

    // Allow address reuse
    _acceptor.set_option(net::socket_base::reuse_address(true));
    if(ec)
    {
        fail(ec, "set_option");
        return;
    }

    // Bind to the server address
    _acceptor.bind(endpoint, ec);
    if(ec)
    {
        fail(ec, "bind");
        return;
    }

    // Start listening for connections
    _acceptor.listen(
            net::socket_base::max_listen_connections, ec);
    if(ec)
    {
        fail(ec, "listen");
        return;
    }

}

void Listener::fail(error_code ec, char const* what){
    if(ec == net::error::operation_aborted)
        return;

    std::cerr << what << ec.message() << "\n";
}
void Listener::onAccept(error_code ec){

    if(ec)
        fail(ec, "accept");
    else{
        std::make_shared<HttpSession>(std::move(_socket), _state)->run();
    }

    run();
}

void Listener::run(){
    _acceptor.async_accept(_socket,
                           [self = shared_from_this()](error_code ec)
    {
        self->onAccept(ec);
    });
}



}