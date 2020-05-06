//
// Created by pawel on 04.05.2020.
//

#include "UdpHandler.h"

UdpHandler::UdpHandler(std::shared_ptr<UdpConnection> &connection) {
    this->connection = connection;
    this->game = nullptr;
    active = true;
}


void UdpHandler::start() {
    sendInitPackets();
    gameStatusReader = std::thread(&UdpHandler::recvGameState, this);
    commandsSender = std::thread(&UdpHandler::sendCommandsToServer, this);
}

void UdpHandler::sendCommandsToServer() {
    while(active && game->isRunning()){
        std::string command = game->getNextCommand();
        if(command == protocol::end_of_game) {
            active = false;
            break;
        }
        connection->sendPacket(command.c_str());
    }
}

void UdpHandler::recvGameState() {
    while(!game->isFinished() && active) {
        std::string state = connection->readPacket();
        if(!state.empty())
            game->getUdpUpdate(state);
    }
}

void UdpHandler::sendInitPackets() {
    while(!game->isRunning() && !game->isFinished() && active){
        connection->sendPacket(init_packet.c_str());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void UdpHandler::disable() {
    active = false;
}

void UdpHandler::enable() {
    active = true;
}

void UdpHandler::attachGame(std::shared_ptr<Game> &game) {
    this->game = game;
}

void UdpHandler::setInitPacket(std::string init_packet) {
    this->init_packet = init_packet;
}

UdpHandler::~UdpHandler() {
    active = false;
    gameStatusReader.join();
    commandsSender.join();
}

