
#include "Tests.h"
#include "Recipe1.h"
#include "Recipe2.h"
#include "Recipe3.h"
#include "Recipe4.h"
#include "Recipe5.h"
#include "Recipe6.h"
#include "Recipe8.h"
#include "Recipe9.h"
#include "Recipe10.h"
#include "Recipe11.h"
#include "Recipe12.h"
#include "Recipe13.h"
#include "Recipe14.h"
#include "Recipe15.h"
#include "BasicIntroduction.h"


//#include <boost/asio.hpp>
//#include <iostream>
//using boost::asio::ip::tcp;
//
//int main() {
//    try {
//        boost::asio::io_service io_service;
//        tcp::resolver resolver(io_service);
//        tcp::resolver::query query("google.com", "http");
//        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
//        tcp::socket socket(io_service);
//        boost::asio::connect(socket, endpoint_iterator);
//        boost::asio::streambuf request;
//        std::ostream request_stream(&request);
//        request_stream << "GET / HTTP/1.1\r\n";
//        request_stream << "Host: google.com\r\n";
//        request_stream << "Accept: */*\r\n";
//        request_stream << "Connection: close\r\n\r\n";
//        boost::asio::write(socket, request);
//        boost::asio::streambuf response;
//        boost::asio::read_until(socket, response, "\r\n");
//        std::istream response_stream(&response);
//        std::string http_version;
//        response_stream >> http_version;
//        unsigned int status_code;
//        response_stream >> status_code;
//        std::string status_message;
//        std::getline(response_stream, status_message);
//        if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
//            std::cout << "Invalid response\n";
//            return 1;
//        }
//        if (status_code != 200) {
//            std::cout << "Response returned with status code " << status_code << "\n";
//            return 1;
//        }
//        boost::asio::read_until(socket, response, "\r\n\r\n");
//        std::string header;
//        while (std::getline(response_stream, header) && header != "\r") {
//            std::cout << header << "\n";
//        }
//        std::cout << "\n";
//        if (response.size() > 0) {
//            std::cout << &response;
//        }
//    } catch (std::exception& e) {
//        std::cout << "Exception: " << e.what() << "\n";
//    }
//    return 0;
//}


int main()
{
    return BasicIntroduction::execute();
}
