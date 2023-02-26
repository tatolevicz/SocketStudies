//
// Created by Arthur Motelevicz on 25/02/23.
//

#include "Listener.h"
#include "SharedState.h"
#include "HttpSession.h"

namespace gr_video{

Listener::Listener(net::io_context& ioc, tcp::endpoint endpoint, std::shared_ptr<SharedState> const& state):
_acceptor(ioc),
_socket(ioc,endpoint)
{


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