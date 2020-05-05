//
// Created by pawel on 29.04.2020.
//

#include "Connection.h"

void Connection::closeSocket() {
    close(sockfd);
}

Connection::Connection() {
    sockfd = -1;
    memset( (char *)&server_address, 0, sizeof(server_address) );
}

Connection::~Connection() {
    if(sockfd > 0)
        closeSocket();
}
