//
// Created by Arthur Motelevicz on 25/02/23.
//

#include "ServerTests.h"
#include "Common.h"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/algorithm/string.hpp>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <iostream>
#include <string>
#include "AsyncHandShake.h"
using namespace boost;

std::shared_ptr<std::string> data;


std::string generate_websocket_accept_key(const std::string& websocket_key) {
    const std::string websocket_magic_string = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    std::string concatenated_key = websocket_key + websocket_magic_string;

    unsigned char hashed_bytes[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(concatenated_key.c_str()), concatenated_key.length(), hashed_bytes);

    char encoded_key[28];
    EVP_EncodeBlock(reinterpret_cast<unsigned char*>(encoded_key), hashed_bytes, SHA_DIGEST_LENGTH);

    return std::string(encoded_key, 28);
}

std::string handle_websocket_request(const std::string& request) {
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

void ServerTests::readHeaderAsync(boost::asio::ip::tcp::socket& sock){
    data.reset(new std::string);
    asio::async_read_until(sock,
                           boost::asio::dynamic_buffer(*data),
                           "\r\n\r\n",
                           std::bind(readHeaderCB, std::placeholders::_1, std::placeholders::_2, &sock));
}


void ServerTests::readHeaderCB(const boost::system::error_code& ec,
                               const std::size_t bytes_read,
                               boost::asio::ip::tcp::socket* sock){

    CHECK_ERROR_VOID(ec)

    for(int i = 0; i < bytes_read; i++)
        std::cout << (*data)[i];

    auto responseHeader = handle_websocket_request(*data);

    writeAcceptHeaderAsync(*sock, responseHeader);
}


void ServerTests::readAsync(boost::asio::ip::tcp::socket& sock){

    const std::size_t READ_SIZE = 1;
    char* buf = new char[READ_SIZE];
    asio::mutable_buffers_1 inputBuffer = asio::buffer(buf, READ_SIZE);
    asio::async_read(sock, inputBuffer, std::bind(readCB_2, std::placeholders::_1, std::placeholders::_2, &sock, buf));
}


void ServerTests::readCB_2(const boost::system::error_code& ec,
                         const std::size_t bytes_read,
                         boost::asio::ip::tcp::socket* sock,
                         const char* buf){

    CHECK_ERROR_VOID(ec)

    for(int i = 0; i < bytes_read; i++)
        std::cout <<buf[i];


    readAsync(*sock);
}


void ServerTests::writeAcceptHeaderAsync(boost::asio::ip::tcp::socket& sock, const std::string& responseHeader){

    asio::const_buffers_1 outputBuffer = asio::buffer(responseHeader.data(),responseHeader.size());

    system::error_code ec;
    asio::write(sock, outputBuffer,ec);
    CHECK_ERROR_VOID(ec)
}

int ServerTests::execute(){

    system::error_code ec;
    asio::io_context ioc;

    //enpoint
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(),1234);
    CHECK_ERROR(ec)

    //socket - to read the accepted connection
//    asio::ip::tcp::socket sock(ioc);
    std::shared_ptr<asio::ip::tcp::socket> sock(new asio::ip::tcp::socket(ioc));

    //acceptor accept
    asio::ip::tcp::acceptor acpt (ioc, ep);

    //wait for incomming clients
    acpt.accept(*sock,ec);
    CHECK_ERROR(ec)

    //run read async in a thread and write async in another
//    readHeaderAsync(sock);
    auto asyncHandShake = AsyncHandShake(sock, [](const system::error_code&  ec){
        std::cout << "\n\nOnHandShake completed: " << ec.value() << "\n\n";
    });

    asyncHandShake.execute();

    ioc.run();

    return 0;
}




//
//int main() {
//    std::string request = "GET / HTTP/1.1\r\n"
//                          "Sec-WebSocket-Key: EuXJlXBmGmDUtOoYFamVtA==\r\n"
//                          "Connection: Upgrade\r\n"
//                          "Upgrade: websocket\r\n"
//                          "Sec-WebSocket-Extensions: permessage-deflate; client_max_window_bits\r\n"
//                          "Host: localhost:1234\r\n\r\n";
//
//    handle_websocket_request(request);
//    return 0;
//}
