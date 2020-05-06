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
    std::shared_ptr<TcpConnection> tcp;
    std::shared_ptr<UdpConnection> udp;
    std::shared_ptr<TcpHandler> tcp_handler;
    std::shared_ptr<UdpHandler> udp_handler;
public:
    GameManager();
    ~GameManager();
    void setUpTcpConnection();
    void setUpUdpSocket();
    void initGame(std::shared_ptr<Game> game);
    std::string getInitPacket(std::shared_ptr<Game> &game);
};


#endif //TIN_GAMEMANAGER_H
