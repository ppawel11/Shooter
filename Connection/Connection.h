//
// Created by pawel on 29.04.2020.
//

#ifndef TIN_CONNECTION_H
#define TIN_CONNECTION_H

#include "../common.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iostream>

class Connection {
protected:
    int sockfd;
    struct sockaddr_in server_address;
public:
    Connection();
    ~Connection();
    virtual void initSocket() = 0;
    virtual void sendPacket(const char *buf, int len) = 0;
    virtual std::string readPacket() = 0;
    void closeSocket();
};


#endif //TIN_CONNECTION_H
