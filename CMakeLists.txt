cmake_minimum_required(VERSION 3.24)
project(Socket)

set(CMAKE_CXX_STANDARD 17)

add_executable(Socket main.cpp BookRecipes/Recipe1.cpp BookRecipes/Recipe1.h BookRecipes/Recipe2.cpp BookRecipes/Recipe2.h BookRecipes/Common.h BookRecipes/Recipe3.cpp BookRecipes/Recipe3.h BookRecipes/Recipe4.cpp BookRecipes/Recipe4.h)

find_package(Boost REQUIRED)
if (${Boost_FOUND})
    target_include_directories( ${PROJECT_NAME} PUBLIC
            ${Boost_INCLUDE_DIRS}
            )
else()
    message(FATAL_ERROR "Boost not found please install it!")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
        BookRecipes
        )
