//
// Created by pawel on 29.04.2020.
//

#ifndef TIN_TCPCONNECTION_H
#define TIN_TCPCONNECTION_H

#include "Connection.h"
#include <mutex>

class TcpConnection: public Connection {
    std::mutex * mutex_send_recv;
public:
    TcpConnection();
    ~TcpConnection() =default;
    void initSocket() override;
    void sendPacket(const char *buf) override;
    std::string readPacket() override;

    void connectToServer();
};


#endif //TIN_TCPCONNECTION_H
