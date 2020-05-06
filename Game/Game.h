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

class Game {
    bool running;
    bool finished;
    std::string game_id;
    int commands_counter;
    BlockingQueue<std::string> commands_to_send;
    std::thread main_thread;
    std::mutex over;
public:
    Game();
    void start();
    void stop();
    bool isRunning();
    bool isFinished();
    void disconnect();
    const std::string &getGameId() const;
    std::string getNextCommand();
    void getTcpUpdate(std::string &update);
    void getUdpUpdate(std::string &update);
    void addCommand(std::string command);
    void addCommands(); // only for testing
    void waitUntilOver();
};


#endif //TIN_GAME_H
