#include "Game/Game.h"
#include "Game/GameManager.h"

int main() {
    std::shared_ptr<Game> game = std::make_shared<Game>();
    std::shared_ptr<GameManager> game_manager = std::make_shared<GameManager>();

    game_manager->setUpTcpConnection();
    game_manager->setUpUdpSocket();

    game_manager->initGame(game);

    game->waitUntilOver();

    return 0;
}
