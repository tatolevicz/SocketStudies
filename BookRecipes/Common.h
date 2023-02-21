//
// Created by Arthur Motelevicz on 20/02/23.
//

#ifndef SOCKET_COMMON_H
#define SOCKET_COMMON_H

#include <boost/asio.hpp>
#include <iostream>

#define CHECK_ERROR(ec) \
    if ((ec).value() != 0) { \
        std::cerr << "Failed to parse ip address: " << (ec).value() << " Message: " << (ec).message() << "\n"; \
        return (ec).value(); \
    }

#endif //SOCKET_COMMON_H
