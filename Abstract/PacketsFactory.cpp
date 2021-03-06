//
// Created by qt on 12.05.2020.
//

#include "PacketsFactory.h"
#include <iostream>
std::shared_ptr<Packet> PacketsFactory::createPacket(std::string & message) {
    switch(message[0]){
        case protocol::init_packet_mark:
            return std::make_shared<InitPacket>(message);
        case protocol::starting_packet_mark:
            return std::make_shared<StartingPacket>(message);
        case protocol::game_state_packet_mark:
            return std::make_shared<GameStatePacket>(message);
        case protocol::end_of_game_mark:
            return std::make_shared<EndOfGamePacket>(message);
        default:
            throw std::runtime_error("unrecognized packet");
    }
}
