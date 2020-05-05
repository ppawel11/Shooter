//
// Created by pawel on 03.05.2020.
//

#ifndef TIN_GAMEMANAGER_H
#define TIN_GAMEMANAGER_H

#include "../Connection/TcpConnection.h"
#include "../Connection/UdpConnection.h"
#include "../Connection/TcpHandler.h"
#include "../Connection/UdpHandler.h"
#include "Game.h"

class GameManager {
    TcpConnection * tcp;
    UdpConnection * udp;
    TcpHandler * tcp_handler;
    UdpHandler * udp_handler;
public:
    GameManager();
    ~GameManager();
    void setUpTcpConnection();
    void setUpUdpSocket();
    void initGame(Game * game);
    std::string getInitPacket(Game * game);
};


#endif //TIN_GAMEMANAGER_H
