//
// Created by Arthur Motelevicz on 01/04/23.
//

#include "PingPongCloseTests.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>

using namespace boost;

// Implementar um websocket server de echo com ping pong e close control frames
int PingPongCloseTests::execute() {

    /**
     *   1) criar o contexto para iniciar o socket e o acceptor
     *   2) criar o socket ativo
     *   3) criar o end point do server com a porta
     *   4) inicializar o acceptor async dentro de um loop infito e um try catch
     *   5) fazer o handshake com o http protocol usando a beast
     *   6) se sucesso inicializar o websocket beast pra
     *   7) entrar no loop de leitura e escrita do socket ativo
     */

    //Todo: resolve a generic endpoint

    asio::io_context ioc;

    asio::ip::tcp::socket sock(ioc);

    asio::ip::tcp::endpoint ep(asio::ip::make_address("127.0.0.1"), 1234);

    asio::ip::tcp::acceptor acceptor(ioc);

    beast::flat_buffer httpBuffer;
    beast::flat_buffer socketBuffer;
    beast::http::request<beast::http::string_body> httpReq;

    std::shared_ptr<beast::websocket::stream<asio::ip::tcp::socket>> socketStream;

    std::vector<std::shared_ptr<std::string>> messagesQueue;

    auto sendPing = [&]() {

        std::thread worker = std::thread([&]() {
            std::this_thread::sleep_for(std::chrono::seconds(5));

            // Criar um objeto ping_data
            beast::websocket::ping_data ping;

            // Enviar o ping
            socketStream->async_ping(ping, [](boost::system::error_code ec) {
                if (ec) {
                    std::cerr << "Erro ao enviar ping: " << ec.message() << std::endl;
                } else {
                    std::cout << "Ping enviado com sucesso" << std::endl;
                }
            });
        });

        worker.detach();
    };


    using ReadWriteCB = std::function<void(system::error_code ec, std::size_t bytes)>;

    auto checkError = [](system::error_code ec, int line = 0) {
        if (ec) {
            std::cerr << "Line " << line << "Error number: " << ec.value() << " Message: " << ec.message() << "\n";
            return ec.value();
        }
        return 0;
    };

    ReadWriteCB onWriteSocket = [&](system::error_code ec, std::size_t bytes) {
        if (ec) {
            checkError(ec, __LINE__);
        }

        messagesQueue.erase(messagesQueue.begin());

        if (!messagesQueue.empty())
            socketStream->async_write(asio::buffer(*messagesQueue.front()), onWriteSocket);
    };

    ReadWriteCB onReadSocket = [&](system::error_code ec, std::size_t bytes) {

        if (checkError(ec, __LINE__))
            return;


        //debug the payload message received
        std::string result(boost::asio::buffer_cast<const char *>(socketBuffer.data()), socketBuffer.size());
        std::cout << "Message: " << result << "\n";

        //save the message to write queue
        messagesQueue.push_back(std::make_shared<std::string>(std::move(result)));

        socketBuffer.consume(socketBuffer.size());
        socketStream->async_read(socketBuffer, onReadSocket);

        //call the writing loop
        socketStream->async_write(asio::buffer(*messagesQueue.front()), onWriteSocket);

        //schedule a ping to 5 sec after receive a message
        sendPing();
    };

    auto onHandShake = [&](system::error_code ec) {
        if (checkError(ec, __LINE__))
            return;

        socketStream->async_read(socketBuffer, onReadSocket);
    };

    ReadWriteCB onReadHttp = [&](system::error_code ec, std::size_t bytes) {

        if (ec == beast::http::error::end_of_stream) {
            sock.shutdown(asio::ip::tcp::socket::shutdown_send, ec);
            return;
        }

        /**
         * Pelo meu entendimento até agora por se tratar de uma leitura não
         * é necessário limpar o buffer pois ele só grava os dados na memoria e
         * a beast por baixo faz o parse para a request que sim é usado para acessar os dados
         * da requisição.
         */

        //debug incoming resquest
//        httpBuffer.commit(bytes);
//        std::string requestStr = beast::buffers_to_string(httpBuffer.data());
//        std::cout << requestStr;
//        httpBuffer.consume(httpBuffer.size());

        if (checkError(ec, __LINE__))
            return;

        //example how to check if there is some specific header
//        bool has_socket_header = httpReq.find(beast::http::field::sec_websocket_key) != httpReq.end();
        //or literally
        bool has_socket_header = httpReq.find("Sec-WebSocket-Key") != httpReq.end();

        if (has_socket_header)
            std::cout << "Header Socket in there = ) : " << httpReq.at(beast::http::field::sec_websocket_key) << "\n";

        if (beast::websocket::is_upgrade(httpReq)) {
            socketStream = std::make_shared<beast::websocket::stream<asio::ip::tcp::socket>>(std::move(sock));

            //now socket is connected and can be used to watch control messages
            socketStream->control_callback(
            [](boost::beast::websocket::frame_type kind, string_view payload)
            {
                switch (kind) {
                    case boost::beast::websocket::frame_type::ping:
                    {
                        std::cout << "Ping message received! Payload: "<< payload << "\n";
                        return;
                    }
                    case boost::beast::websocket::frame_type::pong:
                    {
                        std::cout << "Pong message received! Payload: "<< payload << "\n";
                        return;
                    }
                    case boost::beast::websocket::frame_type::close:
                    {
                        std::cout << "Close message received! Payload: "<< payload << "\n";
                        return;
                    }
                }

            });

            //do the handshake
            socketStream->async_accept(httpReq, onHandShake);
            return;
        }

        httpReq.clear();
    };


    auto onAccept = [&](system::error_code ec) {
        if (checkError(ec, __LINE__))
            return;

        //entra no handshake
        beast::http::async_read(sock, httpBuffer, httpReq, onReadHttp);
    };


    system::error_code ec;

    // Open the acceptor
    acceptor.open(ep.protocol(), ec);
    if (checkError(ec, __LINE__))
        return ec.value();

    // Allow address reuse
    acceptor.set_option(asio::socket_base::reuse_address(true));
    if (checkError(ec, __LINE__))
        return ec.value();

    // Bind to the server address
    acceptor.bind(ep, ec);
    if (checkError(ec, __LINE__))
        return ec.value();

    // Start listening for connections
    acceptor.listen(
            asio::socket_base::max_listen_connections, ec);
    if (checkError(ec, __LINE__))
        return ec.value();

    acceptor.async_accept(sock, ep, onAccept);







    ioc.run();

    return 0;

}