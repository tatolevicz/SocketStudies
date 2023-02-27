//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "WebsocketConnection.h"
#include "ServerState.h"

//server beast
namespace sb {

WebsocketConnection::WebsocketConnection(boost::asio::ip::tcp::socket sock,
                                         std::shared_ptr<ServerState> serverState):
_sockStream(std::move(sock)),
_serverState(std::move(serverState))
{

}

WebsocketConnection::~WebsocketConnection(){
    _serverState->leave(this);
}

void WebsocketConnection::send(const std::string& message){
    _messageQueue.push_back(message);
    callAsyncWrite();
}

void WebsocketConnection::onRead(boost::system::error_code ec, std::size_t bytes){

    CHECK_ASIO_ERROR_(ec)

    std::string message = boost::beast::buffers_to_string(_buffer.data());
    std::cout << "Msg: " << message << "\n";

    _buffer.consume(bytes);

    _serverState->send(message);

    callAsyncRead();
}

void WebsocketConnection::callAsyncRead() {
    _sockStream.async_read(_buffer,[self = shared_from_this()](boost::system::error_code ec, std::size_t bytes){
        self->onRead(ec, bytes);
    });
}

void WebsocketConnection::callAsyncWrite(){
    _sockStream.async_write(boost::asio::buffer(_messageQueue.front()),
        [self = shared_from_this()](boost::system::error_code ec, std::size_t bytes){
            self->onWrite(ec, bytes);
        });
}

void WebsocketConnection::onHandShake(boost::system::error_code ec){

    CHECK_ASIO_ERROR_(ec)
    _serverState->join(this);
    callAsyncRead();
}

void WebsocketConnection::onWrite(boost::system::error_code ec, std::size_t bytes){

    CHECK_ASIO_ERROR_(ec)
    _messageQueue.erase(_messageQueue.begin());

    if(!_messageQueue.empty()){
        callAsyncWrite();
    }
}

void WebsocketConnection::run(boost::beast::http::request<boost::beast::http::string_body>& _req){
    _sockStream.async_accept(_req, [self = shared_from_this()](boost::system::error_code ec){
        self->onHandShake(ec);
    });
}

}
