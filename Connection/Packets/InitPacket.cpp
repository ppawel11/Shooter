//
// Created by pawel on 12.05.2020.
//

#include "InitPacket.h"
#include "../../Game/Game.h"

InitPacket::InitPacket(std::string &message) {
    client_id = (unsigned int)message[1];
}

int InitPacket::getClientId() const {
    return client_id;
}

void InitPacket::beHandled(Game *game) {
    game->handle(this);
}
