//
// Created by pawel on 04.05.2020.
//

#include "UdpHandler.h"

UdpHandler::UdpHandler(std::shared_ptr<UdpConnection> &connection) {
    this->connection = connection;
    this->game = nullptr;
    active = true;
    crc = CrcModule();
}


void UdpHandler::start() {
    sendInitPackets();
    game_state_reader = std::thread(&UdpHandler::recvGameState, this);
    commands_sender = std::thread(&UdpHandler::sendCommandsToServer, this);
}

void UdpHandler::sendCommandsToServer() {
    while(active && game->isRunning()){
        std::string command = game->getNextCommand();
        if(command == protocol::end_of_game) {
            active = false;
            break;
        }
        std::string command_with_crc = crc.getMessageWithCrc(command);
        connection->sendPacket(command_with_crc.c_str(), command_with_crc.length());
    }
}

void UdpHandler::recvGameState() {
    while(!game->isFinished() && active) {
        std::string state = connection->readPacket();
        if(!state.empty() && crc.checkAndRemoveMessageSum(state))
            game->getUpdate(state);
    }
}

void UdpHandler::sendInitPackets() {
    while(!game->isRunning() && !game->isFinished() && active){
        std::string init_packet_crc = crc.getMessageWithCrc(init_packet);
        connection->sendPacket(init_packet_crc.c_str(), init_packet_crc.length());
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
    game_state_reader.join();
    commands_sender.join();
}

