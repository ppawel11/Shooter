//
// Created by pawel on 04.05.2020.
//

#ifndef TIN_UDPHANDLER_H
#define TIN_UDPHANDLER_H

#include "UdpConnection.h"
#include "../Game/Game.h"
#include <thread>

class UdpHandler {
    UdpConnection * connection;
    std::thread initPacketSender;
    std::thread commandsSender;
    std::thread gameStatusReader;
    bool active;
    std::string init_packet;
    Game* game;
public:
    UdpHandler(UdpConnection *connection);
    ~UdpHandler();
    void attachGame(Game * game);
    void start();
    void sendCommandsToServer();
    void recvGameState();
    void sendInitPackets();
    void disable();
    void enable();
    void setInitPacket(std::string init_packet);
};


#endif //TIN_UDPHANDLER_H
