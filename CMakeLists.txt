cmake_minimum_required(VERSION 3.24)
project(Socket)

set(CMAKE_CXX_STANDARD 17)

add_executable(Socket main.cpp
        BookRecipes/Recipe1.cpp BookRecipes/Recipe1.h BookRecipes/Recipe2.cpp BookRecipes/Recipe2.h BookRecipes/Common.h BookRecipes/Recipe3.cpp BookRecipes/Recipe3.h BookRecipes/Recipe4.cpp BookRecipes/Recipe4.h BookRecipes/Recipe5.cpp BookRecipes/Recipe5.h BookRecipes/Recipe6.cpp BookRecipes/Recipe6.h BookRecipes/Recipe8.cpp BookRecipes/Recipe8.h BookRecipes/Tests.cpp BookRecipes/Tests.h BookRecipes/Recipe9.cpp BookRecipes/Recipe9.h BookRecipes/Recipe10.cpp BookRecipes/Recipe10.h BookRecipes/Recipe11.cpp BookRecipes/Recipe11.h BookRecipes/Recipe12.cpp BookRecipes/Recipe12.h BookRecipes/Recipe13.cpp BookRecipes/Recipe13.h BookRecipes/Recipe14.cpp BookRecipes/Recipe14.h BookRecipes/Recipe15.cpp BookRecipes/Recipe15.h
        OLC_Playlist/BasicIntroduction.cpp
        OLC_Playlist/BasicIntroduction.h)

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
        OLC_Playlist
        )
