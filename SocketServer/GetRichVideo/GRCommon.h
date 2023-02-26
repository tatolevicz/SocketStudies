//
// Created by Arthur Motelevicz on 25/02/23.
//

#ifndef SOCKET_GRCOMMON_H
#define SOCKET_GRCOMMON_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <unordered_set>
#include <iostream>
//#include "SharedState.h"
//#include "Listener.h"
//#include "HttpSession.h"
//#include "WebsocketSession.h"

namespace gr_video {
    class SharedState;
    class Listener;
    class HttpSession;
    class WebsocketSession;
}

//ASIO
namespace net = boost::asio;
using tcp = net::ip::tcp;
using error_code = boost::system::error_code;

//BEAST
namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace websocket = boost::beast::websocket;

#endif //SOCKET_GRCOMMON_H
