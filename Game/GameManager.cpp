//
// Created by pawel on 03.05.2020.
//

#include "GameManager.h"

GameManager::GameManager() {
    tcp = new TcpConnection();
    udp = new UdpConnection();

    tcp_handler = new TcpHandler(tcp);
    udp_handler = new UdpHandler(udp);
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
    udp->initSocket();
}

void GameManager::initGame(Game * game) {
    tcp_handler->attachGame(game);
    udp_handler->attachGame(game);

    tcp_handler->start();

    udp_handler->setInitPacket(getInitPacket(game));
    udp_handler->start();
}

std::string GameManager::getInitPacket(Game * game) {
    return std::string("X" + game->getGameId());
}

GameManager::~GameManager() {
    tcp_handler->disable();
    udp_handler->disable();

    delete tcp_handler;
    delete udp_handler;

    delete tcp;
    delete udp;
}

