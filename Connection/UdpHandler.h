//
// Created by pawel on 04.05.2020.
//

#ifndef TIN_UDPHANDLER_H
#define TIN_UDPHANDLER_H

#include "UdpConnection.h"
#include "../Game/Game.h"
#include <thread>
#include <memory>

class UdpHandler {
    std::shared_ptr<UdpConnection> connection;
    std::shared_ptr<Game> game;

    std::thread commandsSender;
    std::thread gameStatusReader;

    bool active;
    std::string init_packet;
public:
    UdpHandler(std::shared_ptr<UdpConnection> &connection);
    ~UdpHandler();
    void attachGame(std::shared_ptr<Game> &game);
    void start();
    void sendCommandsToServer();
    void recvGameState();
    void sendInitPackets();
    void disable();
    void enable();
    void setInitPacket(std::string init_packet);
};


#endif //TIN_UDPHANDLER_H
