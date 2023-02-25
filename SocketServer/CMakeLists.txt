cmake_minimum_required(VERSION 3.24)
project(SocketServer)

set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.24)
project(Socket)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp BookServers/Recipe15.cpp BookServers/Recipe15.h BookServers/Common.h BookServers/ServerTests.cpp BookServers/ServerTests.h BookServers/AsyncHandShake.cpp BookServers/AsyncHandShake.h)
find_package(OpenSSL REQUIRED)

if (${OPENSSL_FOUND})
    target_include_directories( ${PROJECT_NAME} PUBLIC
            ${OPENSSL_INCLUDE_DIR}
            )
else()
    message(FATAL_ERROR "OpenSSL not found please install it!")
endif()

find_package(Boost REQUIRED)
if (${Boost_FOUND})
    target_include_directories( ${PROJECT_NAME} PUBLIC
            ${Boost_INCLUDE_DIRS}
            )
else()
    message(FATAL_ERROR "Boost not found please install it!")
endif()

target_link_libraries( ${PROJECT_NAME} PUBLIC
        OpenSSL::SSL OpenSSL::Crypto

)
target_include_directories(${PROJECT_NAME} PUBLIC
        BookServers
        )
