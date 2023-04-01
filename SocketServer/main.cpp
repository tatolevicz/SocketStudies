#include "Recipe15.h"
#include "ServerTests.h"
#include "GR_ChatServer.h"
#include "PageServer.h"
#include "ServerBeast_1.h"
#include "PingPongCloseTests.h"
#include "Server.h"

int main() {
//
    sb::Server s;
    std::thread worker([&](){
        s.start();
    });
    worker.detach();

    bool quit = false;
    while(!quit){
        std::string input;
        std::getline(std::cin, input);

        if(input == "stop"){
            std::cout << "Close all streams!!\n";
            s.stop();
        }
        if(input == "close"){
            std::cout << "Close all streams!!\n";
            s.disconnectAll();
        }
        else if(input == "quit"){
            quit = true;
        }
    }

    return 0;
    return PingPongCloseTests::execute();
}
