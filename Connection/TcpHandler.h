//
// Created by pawel on 03.05.2020.
//

#ifndef TIN_TCPHANDLER_H
#define TIN_TCPHANDLER_H

#include "TcpConnection.h"
#include "../common.h"
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include "../Game/Game.h"

class TcpHandler {
    TcpConnection* connection;
    std::thread keepAliveSender;
    std::thread gameStatusReader;
    bool active;
    Game* game;
public:
    TcpHandler(TcpConnection * connection);
    ~TcpHandler();
    void attachGame(Game * game);
    void start();
    void sendAlivePackets();
    void readGameStatus();
    void getGameId();
    void disable();
    void enable();
};


#endif //TIN_TCPHANDLER_H
