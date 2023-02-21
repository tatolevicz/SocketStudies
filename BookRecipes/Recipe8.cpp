//
// Created by Arthur Motelevicz on 21/02/23.
//

#include "Recipe8.h"
#include <boost/asio.hpp>
#include <iostream>
#include "Common.h"

using namespace boost;

//Recipe 5 -> CREATING BUFFERS
// Page 44 ~=  kindle book: Boost.Asio c++ programing

int Recipe8::execute(){

    //buffer to use in output operations
    const std::string message = "Hello world!";
    asio::const_buffers_1 output_buf = asio::buffer(message);


    //buffer to use in input operations
    const size_t BUF_SIZE = 20;
    std::unique_ptr<char[]> buf(new char[BUF_SIZE]);
    asio::mutable_buffers_1 input_buf = asio::buffer(static_cast<void*>(buf.get()), BUF_SIZE);


    return 0;
}