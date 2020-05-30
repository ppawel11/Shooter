//
// Created by pawel on 12.05.2020.
//

#ifndef TIN_STARTINGPACKET_H
#define TIN_STARTINGPACKET_H

#include "Packet.h"
#include <string>

class Game;

class StartingPacket: public Packet {
    int board_height;
    int board_width;
public:
    StartingPacket(std::string &message);
    void beHandled(Game * game) override;
    int getBoardHeight() const;
    int getBoardWidth() const;
};


#endif //TIN_STARTINGPACKET_H


