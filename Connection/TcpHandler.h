//
// Created by pawel on 03.05.2020.
//

#ifndef TIN_TCPHANDLER_H
#define TIN_TCPHANDLER_H

#include "TcpConnection.h"
#include "../common.h"
#include <thread>
#include <mutex>
#include "../Game/Game.h"

class TcpHandler {
    std::shared_ptr<TcpConnection> connection;
    std::shared_ptr<Game> game;
    std::thread keepAliveSender;
    std::thread gameStatusReader;
    bool active;
public:
    TcpHandler(std::shared_ptr<TcpConnection> &connection);
    ~TcpHandler();
    void attachGame(std::shared_ptr<Game> &game);
    void start();
    void sendAlivePackets();
    void readGameStatus();
    void getGameId();
    void disable();
    void enable();
};


#endif //TIN_TCPHANDLER_H
