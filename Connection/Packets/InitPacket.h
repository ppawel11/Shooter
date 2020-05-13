//
// Created by qt on 12.05.2020.
//

#ifndef TIN_INITPACKET_H
#define TIN_INITPACKET_H

#include <string>
#include "Packet.h"

class Game;

class InitPacket: public Packet {
    int client_id;
public:
    InitPacket(std::string &message);
    void beHandled(Game * game) override ;
    int getClientId() const;
};


#endif //TIN_INITPACKET_H
