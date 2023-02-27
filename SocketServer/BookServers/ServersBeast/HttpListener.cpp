//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "HttpListener.h"
#include "ServerState.h"
#include "WebsocketConnection.h"

//server beast
namespace sb {

HttpListener::HttpListener(boost::asio::ip::tcp::socket sock,
                           std::shared_ptr<ServerState> serverState) :
_sock(std::move(sock)),
_serverState(std::move(serverState))
{

}

void HttpListener::onRead(boost::system::error_code ec, std::size_t bytes){

    CHECK_ASIO_ERROR_(ec)

    if(boost::beast::websocket::is_upgrade(_req)){
        //Todo:: chamar websocket connection

        return;
    }
}

void HttpListener::run() {
    boost::beast::http::async_read(
            _sock,
            _buffer,
            _req,
        [self = shared_from_this()](boost::system::error_code ec,std::size_t bytes){
            self->onRead(ec, bytes);
    });
}

}
