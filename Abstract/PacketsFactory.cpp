//
// Created by qt on 12.05.2020.
//

#include "PacketsFactory.h"

std::shared_ptr<Packet> PacketsFactory::createPacket(std::string &message) {
    switch(message[0]){
        case 'X':
            return std::make_shared<InitPacket>(message);
        case 'S':
            return std::make_shared<StartingPacket>(message);
        case 'Y':
            return std::make_shared<GameStatePacket>(message);
        default:
            throw "unrecognized packet";
    }
}
