//
// Created by pawel on 29.04.2020.
//

#ifndef TIN_UDPCONNECTION_H
#define TIN_UDPCONNECTION_H

#include "Connection.h"

class UdpConnection: public Connection {
    struct sockaddr_in client_address;
public:
    UdpConnection();
    ~UdpConnection() =default;
    void initSocket() override;
    void sendPacket(const char *buf) override;
    std::string readPacket() override;
};


#endif //TIN_UDPCONNECTION_H
