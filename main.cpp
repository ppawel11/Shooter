#include <iostream>
#include "Connection/Connection.h"
#include "common.h"
#include "Connection/TcpConnection.h"
#include "Connection/TcpHandler.h"
#include "Connection/UdpConnection.h"
#include "Game/Game.h"
#include "Game/GameManager.h"

int main() {
    Game * game = new Game();
    GameManager * game_manager = new GameManager();
    game_manager->setUpTcpConnection();
    game_manager->setUpUdpSocket();
    std::thread game_t(&GameManager::initGame, game_manager, game);

    while(!game->isFinished())
        std::this_thread::sleep_for(std::chrono::seconds(1));
    game_t.join();

    return 0;
}
