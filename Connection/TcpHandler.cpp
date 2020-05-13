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
    keep_alive_sender = std::thread(&TcpHandler::sendAlivePackets, this);
    game_info_reader = std::thread(&TcpHandler::recvGameInfo, this);
}

void TcpHandler::sendAlivePackets() {
    while (active) {
        try {
            connection->sendPacket(protocol::alive, protocol::alive_len);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }catch(const char * e){
            active = false;
            game->disconnect();
        }
    }
}

void TcpHandler::recvGameInfo(){
    std::string received;
    while(active){
        received = connection->readPacket();
        if(!received.empty()) {
            game->getUpdate(received);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
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
    keep_alive_sender.join();
    game_info_reader.join();
}
