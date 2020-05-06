#include "Game/Game.h"
#include "Game/GameManager.h"

int main() {
    std::shared_ptr<Game> game = std::make_shared<Game>();
    std::shared_ptr<GameManager> game_manager = std::make_shared<GameManager>();

    game_manager->setUpTcpConnection();
    game_manager->setUpUdpSocket();

    std::thread game_t(&GameManager::initGame, game_manager, game);
    while(!game->isFinished())
        std::this_thread::sleep_for(std::chrono::seconds(1));

    game_t.join();

    return 0;
}
