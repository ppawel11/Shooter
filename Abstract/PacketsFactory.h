//
// Created by qt on 12.05.2020.
//

#ifndef TIN_PACKETSFACTORY_H
#define TIN_PACKETSFACTORY_H

#include <memory>
#include "../Connection/Packets/GameStatePacket.h"
#include "../Connection/Packets/InitPacket.h"
#include "../Connection/Packets/StartingPacket.h"
#include "../common.h"

class PacketsFactory {
public:
    std::shared_ptr<Packet> createPacket(std::string & message);
};


#endif //TIN_PACKETSFACTORY_H
