cmake_minimum_required(VERSION 3.24)
project(Socket)

set(CMAKE_CXX_STANDARD 17)

add_executable(Socket main.cpp)

find_package(Boost REQUIRED)
if (${Boost_FOUND})
    target_include_directories( ${PROJECT_NAME} PUBLIC
            ${Boost_INCLUDE_DIRS}
            )
else()
    message(FATAL_ERROR "Boost not found please install it!")
endif()
