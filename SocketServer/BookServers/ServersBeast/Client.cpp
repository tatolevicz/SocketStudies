//
// Created by Arthur Motelevicz on 26/02/23.
//

#include "Client.h"
#include "ServerState.h"
#include "WebsocketConnection.h"

//server beast
namespace sb {

Client::Client(WebsocketConnection* connection) :
_connection(connection)
{
    _id = ++idCounter;
}

unsigned long Client::getId() const {
    return _id;
}

WebsocketConnection* Client::getConnection(){
    return _connection;
}

}



