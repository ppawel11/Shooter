//
// Created by qt on 11.05.2020.
//

#ifndef UNTITLED_GAMEWINDOW_H
#define UNTITLED_GAMEWINDOW_H

#include "../../common.h"
#include "../../Connection/Packets/GameStatePacket.h"
#include "../../Controller/Controller.h"
#include <mutex>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SDL2/SDL.h>

class Controller;

class GameWindow {
    std::shared_ptr<Controller> controller;
    std::vector<std::shared_ptr<PlayerModel>> players;
    std::vector<std::shared_ptr<BulletModel>> bullets;
    std::mutex ready;
    SDL_Window * view;
    SDL_Renderer * renderer;
    std::array<float, 2> last_position;
    bool active;
public:
    GameWindow(std::shared_ptr<Controller> contr);
    void start();
    void stop();
    void loop();

    direction getDirectionInput();

    void drawComponents();
    void clearScreen();

    void drawPlayerRect(std::shared_ptr<PlayerModel> &player);
    void drawBulletRect(std::shared_ptr<BulletModel> &bullet);
    void decidePlayerRectColor(std::shared_ptr<PlayerModel> &player);
    SDL_Rect setUpPlayerRect(std::shared_ptr<PlayerModel> & player);
    SDL_Rect setUpBulletRect(std::shared_ptr<BulletModel> & bullet);

    void getGameState(GameStatePacket * game_state_packet);
    void updateLastPosition();

    void shoot(int & x, int & y);
};


#endif //UNTITLED_GAMEWINDOW_H
