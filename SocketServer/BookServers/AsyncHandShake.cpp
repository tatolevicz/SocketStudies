//
// Created by Arthur Motelevicz on 25/02/23.
//

#include "AsyncHandShake.h"

using namespace boost;

#define CHECK_ERROR(ec) \
        if((ec).value() != 0){ \
            if(_cb) \
                _cb(ec);      \
            return; \
        }


AsyncHandShake::AsyncHandShake(const std::shared_ptr<boost::asio::ip::tcp::socket>& sock, const OnHandShake cb):
_cb(std::move(cb)),
_sock(sock)
{}

void AsyncHandShake::execute(){
    readHeaderAsync(_sock.get());
}

void AsyncHandShake::readHeaderAsync(boost::asio::ip::tcp::socket* sock){
    _data.reset(new std::string);
    asio::async_read_until(*sock,
                           boost::asio::dynamic_buffer(*_data),
                           "\r\n\r\n",
                           std::bind(&AsyncHandShake::readHeaderCB, this, std::placeholders::_1, std::placeholders::_2, sock));
}

void AsyncHandShake::writeAcceptHeaderAsync(boost::asio::ip::tcp::socket* sock, const std::string& responseHeader){

    asio::const_buffers_1 outputBuffer = asio::buffer(responseHeader.data(),responseHeader.size());

    system::error_code ec;
    asio::write(*sock, outputBuffer,ec);
    CHECK_ERROR(ec)
}

void AsyncHandShake::readHeaderCB(const boost::system::error_code& ec,
                                  const std::size_t bytes_read,
                                  boost::asio::ip::tcp::socket* sock){

    CHECK_ERROR(ec)

    for(int i = 0; i < bytes_read; i++)
        std::cout << (*_data)[i];

    auto responseHeader = handle_websocket_request(*_data);

    writeAcceptHeaderAsync(sock, responseHeader);
}

std::string AsyncHandShake::generate_websocket_accept_key(const std::string& websocket_key) {
    const std::string websocket_magic_string = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    std::string concatenated_key = websocket_key + websocket_magic_string;

    unsigned char hashed_bytes[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(concatenated_key.c_str()), concatenated_key.length(), hashed_bytes);

    char encoded_key[28];
    EVP_EncodeBlock(reinterpret_cast<unsigned char*>(encoded_key), hashed_bytes, SHA_DIGEST_LENGTH);

    return std::string(encoded_key, 28);
}

std::string AsyncHandShake::handle_websocket_request(const std::string& request) {
    // Encontra a chave Sec-WebSocket-Key no cabeçalho de solicitação
    std::string key_prefix = "Sec-WebSocket-Key: ";
    std::string::size_type key_pos = request.find(key_prefix);
    std::string::size_type key_end = request.find("\r\n", key_pos);
    std::string websocket_key = request.substr(key_pos + key_prefix.length(), key_end - key_pos - key_prefix.length());

    // Gera a chave de resposta
    std::string websocket_accept_key_2 = generate_websocket_accept_key(websocket_key);

    // Cria o cabeçalho de resposta
    std::stringstream response;
    response << "HTTP/1.1 101 Switching Protocols\r\n";
    response << "Upgrade: websocket\r\n";
    response << "Connection: Upgrade\r\n";
    response << "Sec-WebSocket-Accept: " << websocket_accept_key_2 << "\r\n\r\n";

//    std::cout << "WebSocket Response:\n" << response.str() << std::endl;
    return response.str();
}

