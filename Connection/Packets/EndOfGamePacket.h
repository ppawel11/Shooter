//
// Created by pawel on 02.06.2020.
//

#ifndef TIN_ENDOFGAMEPACKET_H
#define TIN_ENDOFGAMEPACKET_H

#include "Packet.h"
#include <string>

class Game;

class EndOfGamePacket: public Packet {
    int winner;
public:
    EndOfGamePacket(std::string & message);
    void beHandled(Game *game) override;

    int getWinner() const;
};


#endif //TIN_ENDOFGAMEPACKET_H
