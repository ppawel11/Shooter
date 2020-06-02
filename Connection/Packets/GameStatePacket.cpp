//
// Created by pawel on 12.05.2020.
//

#include "GameStatePacket.h"
#include "../../Game/Game.h"

GameStatePacket::GameStatePacket(std::string &message) {
    unsigned int pos_state_id_byte1 = 0x000000FF & message[2];
    unsigned int pos_state_id_byte2 = 0x0000FF00 & (message[1]<<8);
    state_id = (pos_state_id_byte1 | pos_state_id_byte2);

    int num_of_players = 0;
    for(auto byte = message.begin()+3; (*byte != 0x00) && (byte < message.end()); byte += 6){
        addPlayer(std::string(byte, byte+5));
        ++num_of_players;
    }

    for(auto byte = message.begin()+4+6*num_of_players; byte < message.end(); byte += 4)
        addBullet(std::string(byte, byte+3));
}

void GameStatePacket::addPlayer(std::string && buf) {
    unsigned int id = 0x000000FF & buf[0];
    unsigned int points = 0x000000FF & buf[1];

    unsigned int pos_x_byte1 = 0x000000FF & buf[3];
    unsigned int pos_x_byte2 = 0x0000FF00 & (buf[2]<<8);
    unsigned int pos_y_byte1 = 0x000000FF & buf[5];
    unsigned int pos_y_byte2 = 0x0000FF00 & (buf[4]<<8);

    auto pos_x = (float)((pos_x_byte1 | pos_x_byte2) / 100.);
    auto pos_y = (float)((pos_y_byte1 | pos_y_byte2) / 100.);

//    auto pos_x = (float)((0x0000FFFF & (buf[2]<<8 | buf[3])) / 100.);
//    auto pos_y = (float)((0x0000FFFF & (buf[4]<<8 | buf[5])) / 100.);
    players.push_back(std::make_shared<PlayerModel>(id, points, pos_x, pos_y));
}

void GameStatePacket::addBullet(std::string &&buf) {
    unsigned int pos_x_byte1 = 0x000000FF & buf[1];
    unsigned int pos_x_byte2 = 0x0000FF00 & (buf[0]<<8);
    unsigned int pos_y_byte1 = 0x000000FF & buf[3];
    unsigned int pos_y_byte2 = 0x0000FF00 & (buf[2]<<8);
    auto pos_x = (float)((pos_x_byte1 | pos_x_byte2) / 100.);
    auto pos_y = (float)((pos_y_byte1 | pos_y_byte2) / 100.);
//    unsigned int x = 0x0000FFFF & (buf[2]<<8 | buf[3]);
//    unsigned int y = 0x0000FFFF & (buf[4]<<8 | buf[5]);
//    auto pos_x = (float)(x / 100.);
//    auto pos_y = (float)(y / 100.);
    bullets.push_back(std::make_shared<BulletModel>(pos_x, pos_y));
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

const std::vector<std::shared_ptr<BulletModel>> &GameStatePacket::getBullets() const {
    return bullets;
}

