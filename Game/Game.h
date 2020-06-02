//
// Created by pawel on 29.04.2020.
//

#ifndef TIN_GAME_H
#define TIN_GAME_H


#include <string>
#include <iostream>
#include "../common.h"
#include <queue>
#include <thread>
#include "../Abstract/BlockingQueue.h"
#include "../Controller/Controller.h"
#include "../Connection/Packets/StartingPacket.h"
#include "../Connection/Packets/InitPacket.h"
#include "../Connection/Packets/GameStatePacket.h"
#include "../Connection/Packets/EndOfGamePacket.h"
#include "../Abstract/PacketsFactory.h"

class Packet;
class Controller;

class Game {
    bool running;
    bool finished;
    int player_id;
    direction going;
    BlockingQueue<std::string> commands_to_send;
    std::mutex over;
    std::mutex ready;
    std::shared_ptr<Controller> controller;
    PacketsFactory packet_factory;
    int current_id;

public:
    Game(std::shared_ptr<Controller> contr);
    void start();
    void stop();
    bool isRunning();
    bool isFinished();
    void disconnect();
    const int getGameId();
    std::string getNextCommand();
    void getUpdate(std::string &update);
    void addCommand(std::string command);
    void waitUntilOver();

    // Player actions:
    void shoot(int angle);
    void move(direction to_go);

    // Packet handlers:
    void handle(InitPacket *init_packet);
    void handle(StartingPacket *start_packet);
    void handle(GameStatePacket *game_state_packet);
    void handle(EndOfGamePacket *end_packet);
};


#endif //TIN_GAME_H
