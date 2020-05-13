//
// Created by qt on 12.05.2020.
//

#ifndef TIN_GAMESTATEPACKET_H
#define TIN_GAMESTATEPACKET_H

#include "../../Model/PlayerModel.h"
#include "Packet.h"
#include <memory>
#include <vector>
#include <string>

class Game;

class GameStatePacket: public Packet {
    std::vector<std::shared_ptr<PlayerModel>> players;
    int state_id;
public:
    GameStatePacket(std::string & message);
    void beHandled(Game * game) override;

    const std::vector<std::shared_ptr<PlayerModel>> &getPlayers() const;

    int getStateId() const;
};


#endif //TIN_GAMESTATEPACKET_H
