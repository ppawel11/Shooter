#include "Game/Game.h"
#include "Game/GameManager.h"
#include "Controller/Controller.h"
#include "View/GameWindow/GameWindow.h"
#include <SDL2/SDL.h>


int main() {
    std::shared_ptr<Controller> contr = std::make_shared<Controller>();
    std::shared_ptr<Game> game = std::make_shared<Game>(contr);
    std::shared_ptr<GameManager> game_manager = std::make_shared<GameManager>();
    std::shared_ptr<GameWindow> window = std::make_shared<GameWindow>();

    contr->attachGame(game);
    contr->attachGameWindow(window);

    game_manager->setUpTcpConnection();
    game_manager->setUpUdpSocket();

    game_manager->initGame(game);

    game->waitUntilOver();
//    SDL_Quit();

    return 0;
}
