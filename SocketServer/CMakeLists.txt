cmake_minimum_required(VERSION 3.24)
project(SocketServer)

set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.24)
project(Socket)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        main.cpp
        BookServers/Recipe15.cpp
        BookServers/Recipe15.h
        BookServers/Common.h
        BookServers/ServerTests.cpp
        BookServers/ServerTests.h
        BookServers/AsyncHandShake.cpp
        BookServers/AsyncHandShake.h
        GetRichVideo/GR_ChatServer.cpp
        GetRichVideo/GR_ChatServer.h
        GetRichVideo/GRCommon.h
        GetRichVideo/SharedState.cpp
        GetRichVideo/SharedState.h
        GetRichVideo/Listener.cpp
        GetRichVideo/Listener.h
        GetRichVideo/HttpSession.cpp
        GetRichVideo/HttpSession.h
        GetRichVideo/WebsocketSession.cpp
        GetRichVideo/WebsocketSession.h
        BookServers/PageServer.cpp
        BookServers/PageServer.h
        BookServers/ServerBeast_1.cpp
        BookServers/ServerBeast_1.h
        BookServers/ServersBeast/Client.h BookServers/ServersBeast/Client.cpp BookServers/ServersBeast/ServerState.cpp BookServers/ServersBeast/ServerState.h BookServers/ServersBeast/Server.cpp BookServers/ServersBeast/Server.h BookServers/ServersBeast/Doorman.cpp BookServers/ServersBeast/Doorman.h BookServers/ServersBeast/HttpListener.cpp BookServers/ServersBeast/HttpListener.h BookServers/ServersBeast/WebsocketConnection.cpp BookServers/ServersBeast/WebsocketConnection.h BookServers/PingPongCloseTests.cpp BookServers/PingPongCloseTests.h)



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
        OLC_Playlist
        GetRichVideo
        BookServers/ServersBeast
        )
