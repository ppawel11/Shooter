//
// Created by pawel on 11.05.2020.
//

#ifndef TIN_CONTROLLER_H
#define TIN_CONTROLLER_H

#include "../Game/Game.h"
#include "../View/GameWindow/GameWindow.h"
#include "../Connection/Packets/GameStatePacket.h"

class Game;

class Controller
{
private:
    std::shared_ptr<Game> game_observer;
    std::shared_ptr<GameWindow> game_window_observer;

    std::thread window_thread;

public:
    Controller();

    void attachGame(std::shared_ptr<Game>);
    void attachGameWindow(std::shared_ptr<GameWindow>);

    void updateWindow(GameStatePacket * game_state);
    void initWindow();
    void deactivateWindow();
};

#endif //TIN_CONTROLLER_H
