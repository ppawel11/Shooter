//
// Created by pawel on 02.06.2020.
//

#include "EndOfGamePacket.h"
#include "../../Game/Game.h"

void EndOfGamePacket::beHandled(Game *game) {
    game->handle(this);
}

EndOfGamePacket::EndOfGamePacket(std::string &message) {
    winner = (int)message[1];
}

int EndOfGamePacket::getWinner() const {
    return winner;
}
