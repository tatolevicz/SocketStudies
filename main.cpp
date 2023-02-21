#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

void start_reading_from_netcat(ip::tcp::socket& socket)
{
    char buf[1024];
    async_read(socket, buffer(buf), [&socket,buf](const boost::system::error_code& error, std::size_t bytes_transferred) {
        if (!error) {
            std::string msg(buf, bytes_transferred);
            std::cout << "Received message from netcat: " << msg << std::endl;
        }
        else {
            std::cerr << "Error receiving message from netcat: " << error.message() << std::endl;
        }
        start_reading_from_netcat(socket);
    });
}

void start_reading_from_stdin(ip::tcp::socket& socket, std::string& input_buf)
{
    async_read_until(socket, dynamic_buffer(input_buf), '\n', [&socket, &input_buf](const boost::system::error_code& error, std::size_t bytes_transferred) {
        if (!error) {
            std::cout << "receiving message from netcat: " << bytes_transferred << " bytes" << std::endl;
        }
        else {
            std::cerr << "Error receiving message from std::cin: " << error.message() << std::endl;
        }

        start_reading_from_stdin(socket, input_buf);

    });
}

int main()
{
    io_context io_context;
    ip::tcp::socket socket(io_context);
    ip::tcp::resolver resolver(io_context);
    connect(socket, resolver.resolve("localhost", "1234"));

    std::cout << "Connected to server." << std::endl;

    start_reading_from_netcat(socket);

    std::string input_buf;
    start_reading_from_stdin(socket, input_buf);

    io_context.run();

    return 0;
}
