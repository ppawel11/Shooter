//
// Created by qt on 12.05.2020.
//

#include "PacketsFactory.h"

std::shared_ptr<Packet> PacketsFactory::createPacket(std::string & message) {
    switch(message[0]){
        case protocol::init_packet_mark:
            return std::make_shared<InitPacket>(message);
        case protocol::starting_packet_mark:
            return std::make_shared<StartingPacket>(message);
        case protocol::game_state_packet_mark:
            return std::make_shared<GameStatePacket>(message);
        default:
            throw "unrecognized packet";
    }
}
