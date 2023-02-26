//
// Created by Arthur Motelevicz on 25/02/23.
//

#ifndef SOCKET_WEBSOCKETSESSION_H
#define SOCKET_WEBSOCKETSESSION_H

#include "GRCommon.h"

namespace gr_video {

//Maintains an active WebSocket session
class WebsocketSession : public std::enable_shared_from_this<WebsocketSession> {
    beast::flat_buffer _buffer;
    websocket::stream<tcp::socket> _ws;
    std::shared_ptr<SharedState> _state;
    std::vector<std::shared_ptr<std::string const>> _queue;

    void fail(error_code ec, char const* what);
    void onAccept(error_code ec);
    void onRead(error_code ec, std::size_t size);
    void onWrite(error_code ec, std::size_t size);
    void callAsyncRead();
    void callAsyncWrite();

public:
    ~WebsocketSession();
    WebsocketSession(tcp::socket socket,
                     std::shared_ptr<SharedState> const& state);
    template<class Body, class Allocator>
    void run(http::request<Body, http::basic_fields<Allocator>> req);

    void send(std::shared_ptr<std::string const> const& ss);


    };

    template<class Body, class Allocator>
    void WebsocketSession::run(http::request<Body, http::basic_fields<Allocator>> req){
        _ws.async_accept(req,
             [self = shared_from_this()](error_code ec){

                 self->onAccept(ec);
             });
    }


}
#endif //SOCKET_WEBSOCKETSESSION_H
