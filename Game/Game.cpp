//
// Created by pawel on 29.04.2020.
//

#include "Game.h"

Game::Game(){
    running = false;
    finished = false;
    commands_counter = 0;
    game_id = "";
}

void Game::start() {
    running = true;
    main_thread = std::thread(&Game::addCommands, this);
    main_thread.detach();
}

void Game::stop(){
    running = false;
    if(!finished)
        finished = true;
    addCommand(std::string(protocol::end_of_game));
}

bool Game::isRunning() {
    return running;
}

void Game::getTcpUpdate(std::string &update){
    if(update[0] == 'X') {
        game_id = update.substr(1);
        std::cout << "GAME ID: " << game_id << std::endl;
    }else if (update == protocol::start){
        start();
    }
    else if(update == protocol::stop) {
        stop();
    }
    std::cout<<"TCP RECV: "<<update<<std::endl;
}

void Game::getUdpUpdate(std::string &update) {
    std::cout<<"UDP RECV: "<<update<<std::endl;
}

void Game::disconnect() {
    std::cout<<"unexpected disconnection"<<std::endl;
    finished = true;
    if(running)
        stop();
}

std::string Game::getNextCommand() {
    return commands_to_send.pop();
}

bool Game::isFinished() {
    return finished;
}

const std::string &Game::getGameId() const {
    return game_id;
}

void Game::addCommands() {
    while(running){
        commands_counter += 100;
        commands_to_send.push(std::string(std::to_string(commands_counter)));
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void Game::addCommand(std::string command) {
    commands_to_send.push(command);
}
