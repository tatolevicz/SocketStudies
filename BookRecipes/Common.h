//
// Created by Arthur Motelevicz on 20/02/23.
//

#ifndef SOCKET_COMMON_H
#define SOCKET_COMMON_H

#include <boost/asio.hpp>
#include <iostream>


#define __STRINGIZE_I(x) #x
#define __STRINGIZE(x) __STRINGIZE_I(x)

#define __MAKE_FILELINE \
    __FILE__ "(" __STRINGIZE(__LINE__) ")"

#define ERROR(msg) \
    "Error in: " << __MAKE_FILELINE << ": " << msg << "\n"


#define CHECK_ERROR(ec) \
    if ((ec).value() != 0) { \
        std::cerr << ERROR(ec.message()); \
        return (ec).value(); \
    }


using boost::asio::ip::tcp;

class Helper {
public:

    using check_endpoint_cb = std::function<void(boost::asio::ip::tcp::endpoint working_end_point)>;


    inline static void async_check_endpoints(tcp::resolver::results_type &endpoints, boost::asio::io_context &io_context,
                               const check_endpoint_cb &cb) {
        // Start the asynchronous operation to check the endpoint
        std::thread t([&, cb] {
            for (const auto &endpoint: endpoints) {
                if (check_endpoint(endpoint, io_context)) {
                    cb(endpoint);
                    return;
                }
            }
        });

        t.detach();
    }

    // This function checks if an endpoint is available
    inline static bool check_endpoint(const tcp::endpoint &endpoint, boost::asio::io_context &io_context) {
        // Create a socket for the endpoint
        tcp::socket socket(io_context);

        // Connect the socket to the endpoint
        boost::system::error_code error;
        socket.connect(endpoint, error);

        return !error;
    }


};

#endif //SOCKET_COMMON_H
