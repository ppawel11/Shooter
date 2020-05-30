//
// Created by pawel on 12.05.2020.
//

#include "StartingPacket.h"
#include "../../Game/Game.h"

StartingPacket::StartingPacket(std::string &message) {
    board_width = (unsigned int)message[1]*512+(uint)message[2];
    board_height = (unsigned int)message[3]*512+(uint)message[4];
}

int StartingPacket::getBoardHeight() const {
    return board_height;
}

int StartingPacket::getBoardWidth() const {
    return board_width;
}

void StartingPacket::beHandled(Game *game) {
    game->handle(this);
}
