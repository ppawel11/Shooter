//
// Created by qt on 12.05.2020.
//

#include "GameStatePacket.h"
#include "../../Game/Game.h"

GameStatePacket::GameStatePacket(std::string &message) {
    state_id = (unsigned int)message[1]*512+(unsigned int)message[2];
    int number_of_players = ((int)message.length() - 3) / 5;
    for(int i = 0; i < number_of_players; ++i){
        int id = message[3+5*i];
        unsigned int pos_x_byte1 = 0x000000FF & message[5+5*i];
        unsigned int pos_x_byte2 = 0x0000FF00 & (message[4+5*i]<<8);
        unsigned int pos_y_byte1 = 0x000000FF & message[7+5*i];
        unsigned int pos_y_byte2 = 0x0000FF00 & (message[6+5*i]<<8);
        auto pos_x = (float)((pos_x_byte1 | pos_x_byte2) / 100.);
        auto pos_y = (float)((pos_y_byte1 | pos_y_byte2) / 100.);
        players.push_back(std::make_shared<PlayerModel>(id, pos_x, pos_y));
    }
}

void GameStatePacket::beHandled(Game *game) {
    game->handle(this);
}

const std::vector<std::shared_ptr<PlayerModel>> &GameStatePacket::getPlayers() const {
    return players;
}

int GameStatePacket::getStateId() const {
    return state_id;
}
