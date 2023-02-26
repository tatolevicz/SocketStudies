//
// Created by Arthur Motelevicz on 25/02/23.
//

#include "WebsocketSession.h"
#include "SharedState.h"

namespace gr_video{

WebsocketSession::~WebsocketSession(){
    _state->leave(*this);
}

WebsocketSession::WebsocketSession(tcp::socket socket, std::shared_ptr<SharedState> const& state):
_ws(std::move(socket)),
_state(state){

}

void WebsocketSession::send(std::shared_ptr<std::string const> const& ss){

    _queue.push_back(ss);

    //are we writing?
    if(_queue.size() > 1)
        return;

    callAsyncWrite();
}

void WebsocketSession::fail(error_code ec, char const* what){

    if(ec == net::error::operation_aborted || ec == websocket::error::closed){
        return;
    }

    std::cerr << what << ": " << ec.message() << "\n";
}

void WebsocketSession::onAccept(error_code ec){

    if(ec)
        return fail(ec, "accept_socket");

    _state->join(*this);

    callAsyncRead();
}

void WebsocketSession::onRead(error_code ec, std::size_t size){

    if(ec)
        return fail(ec, "read_socket");

    _state->send(beast::buffers_to_string(_buffer.data()));

    _buffer.consume(_buffer.size());

    callAsyncRead();
}

void WebsocketSession::onWrite(error_code ec, std::size_t size){

    if(ec)
        return fail(ec, "write_socket");

    _queue.erase(_queue.begin());

    if(!_queue.empty())
        callAsyncWrite();

}

void WebsocketSession::callAsyncRead(){
    _ws.async_read(_buffer,
        [self = shared_from_this()](error_code ec, std::size_t bytes){
           self->onRead(ec, bytes);
        });
}

void WebsocketSession::callAsyncWrite(){
    _ws.async_write(net::buffer(*_queue.front()),
           [self = shared_from_this()](error_code ec, std::size_t bytes){
               self->onWrite(ec, bytes);
           });
}

}