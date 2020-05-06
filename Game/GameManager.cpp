//
// Created by pawel on 03.05.2020.
//

#include "GameManager.h"

GameManager::GameManager() {
    tcp = std::make_shared<TcpConnection>();
    udp = std::make_shared<UdpConnection>();

    tcp_handler = std::make_shared<TcpHandler>(tcp);
    udp_handler = std::make_shared<UdpHandler>(udp);
}

void GameManager::setUpTcpConnection() {
    try{
        tcp->initSocket();
        tcp->connectToServer();
    }catch(char const * e){
        // unable to connect
        std::cout<<e<<std::endl;
        exit(1);
    }
}

void GameManager::setUpUdpSocket() {
    try {
        udp->initSocket();
    }catch(char const * e){
        std::cout<<e<<std::endl;
        exit(1);
    }
}

void GameManager::initGame(std::shared_ptr<Game> game) {
    tcp_handler->attachGame(game);
    udp_handler->attachGame(game);

    tcp_handler->start();

    udp_handler->setInitPacket(getInitPacket(game));
    udp_handler->start();
}

std::string GameManager::getInitPacket(std::shared_ptr<Game> &game) {
    return std::string("X" + game->getGameId());
}

GameManager::~GameManager() {
    tcp_handler->disable();
    udp_handler->disable();
}

