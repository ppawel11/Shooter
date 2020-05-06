//
// Created by pawel on 03.05.2020.
//

#include "TcpHandler.h"

TcpHandler::TcpHandler(std::shared_ptr<TcpConnection> &connection) {
    this->connection = connection;
    this->game = nullptr;
    this->active = true;
}

void TcpHandler::start() {
    keepAliveSender = std::thread(&TcpHandler::sendAlivePackets, this);
    getGameId();
    gameStatusReader = std::thread(&TcpHandler::readGameStatus, this);
}

void TcpHandler::sendAlivePackets() {
    while (active) {
        try {
            connection->sendPacket(protocol::alive);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }catch(const char * e){
            active = false;
            game->disconnect();
        }
    }
}

void TcpHandler::readGameStatus(){
    std::string received;
    while(active){
        received = connection->readPacket();
        if(!received.empty()) {
            game->getTcpUpdate(received);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void TcpHandler::getGameId(){
    std::string received;
    while(active && received.empty()){
        received = connection->readPacket();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout<<"RECEIVED ID : "<<received<<std::endl;
    game->getTcpUpdate(received);
}

void TcpHandler::disable() {
    active = false;
}

void TcpHandler::enable(){
    active = true;
}

void TcpHandler::attachGame(std::shared_ptr<Game> &game) {
    this->game = game;
}

TcpHandler::~TcpHandler() {
    active = false;
    keepAliveSender.join();
    gameStatusReader.join();
}
