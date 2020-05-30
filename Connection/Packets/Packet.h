//
// Created by pawle on 12.05.2020.
//

#ifndef TIN_PACKET_H
#define TIN_PACKET_H

class Game;

class Packet {
public:
    Packet() = default;
    virtual void beHandled(Game *game) = 0;
};


#endif //TIN_PACKET_H
