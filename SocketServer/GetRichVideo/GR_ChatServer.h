//
// Created by Arthur Motelevicz on 25/02/23.
//

#ifndef SOCKET_GR_CHATSERVER_H
#define SOCKET_GR_CHATSERVER_H


/**CHAT SERVER - using asio + beast
 * This class contains the main implementation of the server - here called execute()
 */
namespace gr_video {

    //creates and run the server
    class GR_ChatServer {
    public:
        static int execute();
    };

}

#endif //SOCKET_GR_CHATSERVER_H
