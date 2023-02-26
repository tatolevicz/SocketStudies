//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "PageServer.h"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <string>

namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

int PageServer::execute() {
    try {
        // Criar uma instância do io_service do Boost.Asio
        boost::asio::io_service io_service;

        // Criar um objeto de endpoint para representar o endereço IP e a porta do servidor
        tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), 1234);

        // Criar um objeto acceptor para receber conexões TCP na porta especificada
        tcp::acceptor acceptor(io_service, endpoint);

        while (true) {
            // Criar um objeto de soquete para cada conexão
            tcp::socket socket(io_service);

            // Esperar por uma conexão e criar um objeto de soquete para ela
            acceptor.accept(socket);

            // Criar um objeto de buffer para armazenar a solicitação HTTP recebida
            boost::beast::flat_buffer buffer;

            // Criar um objeto de solicitação HTTP para armazenar a solicitação recebida
            http::request<http::dynamic_body> request;

            // Receber a solicitação HTTP do soquete
            http::read(socket, buffer, request);

            // Criar um objeto de resposta HTTP
            http::response<http::string_body> response;

            // Definir o status de resposta como OK (200)
            response.result(http::status::ok);

            // Definir o corpo da resposta como um arquivo HTML simples
            response.body() = "<html><head><title>Exemplo de servidor HTTP com Boost.Asio e Boost.Beast</title></head><body><h1>Ola mundo!</h1><p>Este eh um exemplo de servidor HTTP implementado com Boost.Asio e Boost.Beast.</p></body></html>";

            // Definir o tipo de conteúdo da resposta como HTML
            response.set(http::field::content_type, "text/html");

            // Definir o tamanho do corpo da resposta
            response.content_length(response.body().size());

            // Enviar a resposta HTTP para o cliente
            http::write(socket, response);
        }
    } catch (std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
