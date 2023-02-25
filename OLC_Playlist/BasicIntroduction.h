//
// Created by Arthur Motelevicz on 23/02/23.
//

#ifndef SOCKET_BASICINTRODUCTION_H
#define SOCKET_BASICINTRODUCTION_H


#include <boost/asio.hpp>

//PART 1 - Video time starts at:
class BasicIntroduction {
public:
    static void grabSomeData(boost::asio::ip::tcp::socket& sock);
    static int execute();
    inline static const unsigned int BYTES_TO_READ = 1024;
    inline static std::vector<char> readBuffer;
};


#endif //SOCKET_BASICINTRODUCTION_H
