//
// Created by qt on 11.05.2020.
//

#ifndef UNTITLED_GAMEWINDOW_H
#define UNTITLED_GAMEWINDOW_H

#include "../../common.h"
#include "../../Connection/Packets/GameStatePacket.h"
#include <mutex>
#include <SDL2/SDL.h>

class GameWindow {
    std::vector<std::shared_ptr<PlayerModel>> players;
    std::mutex ready;
    SDL_Window * view;
    SDL_Renderer * renderer;
    bool active;
public:
    GameWindow();
    void start();
    void stop();
    void loop();
    void getGameState(GameStatePacket * game_state_packet);
};


#endif //UNTITLED_GAMEWINDOW_H
