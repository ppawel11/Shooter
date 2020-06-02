//
// Created by pawel on 12.05.2020.
//

#ifndef TIN_GAMESTATEPACKET_H
#define TIN_GAMESTATEPACKET_H

#include "../../Model/PlayerModel.h"
#include "../../Model/BulletModel.h"
#include "Packet.h"
#include <memory>
#include <vector>
#include <string>

class Game;

class GameStatePacket: public Packet {
    std::vector<std::shared_ptr<PlayerModel>> players;
    std::vector<std::shared_ptr<BulletModel>> bullets;
    unsigned int state_id;

    void addPlayer(std::string && buf);
    void addBullet(std::string && buf);
public:
    GameStatePacket(std::string & message);
    void beHandled(Game * game) override;

    const std::vector<std::shared_ptr<PlayerModel>> &getPlayers() const;

    const std::vector<std::shared_ptr<BulletModel>> &getBullets() const;

    int getStateId() const;
};


#endif //TIN_GAMESTATEPACKET_H
