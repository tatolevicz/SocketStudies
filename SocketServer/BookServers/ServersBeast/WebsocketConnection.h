//
// Created by Arthur Motelevicz on 26/02/23.
//

#ifndef SOCKET_WEBSOCKETCONNECTION_H
#define SOCKET_WEBSOCKETCONNECTION_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>

//server beast
namespace sb {
    class ServerState;

    class WebsocketConnection : public std::enable_shared_from_this<WebsocketConnection> {
    public:
        WebsocketConnection(boost::asio::ip::tcp::socket sock,
                            std::shared_ptr<ServerState> serverState);

        ~WebsocketConnection();

        void run(boost::beast::http::request<boost::beast::http::string_body>& _req);

        void send(const std::string& message);

    private:

        void callAsyncRead();
        void callAsyncWrite();

        void onRead(boost::system::error_code ec, std::size_t bytes);
        void onWrite(boost::system::error_code ec, std::size_t bytes);
        void onHandShake(boost::system::error_code ec);

        std::shared_ptr<ServerState> _serverState{nullptr};
        boost::beast::websocket::stream<boost::asio::ip::tcp::socket> _sockStream;
        boost::beast::flat_buffer _buffer;
        std::vector<std::string> _messageQueue;
    };

}


#endif //SOCKET_WEBSOCKETCONNECTION_H
