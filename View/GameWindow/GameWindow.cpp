//
// Created by qt on 11.05.2020.
//

#include "GameWindow.h"
#include <thread>

GameWindow::GameWindow() {
    view = nullptr;
    renderer = nullptr;
    active = false;
    ready.lock();
}

void GameWindow::start() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw "sdl could not initialize";
    active = true;
    view = SDL_CreateWindow("Shooter X", 100, 100, window::width, window::height,SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer( view, -1, SDL_RENDERER_ACCELERATED);
    ready.unlock();
    loop();
}

void GameWindow::loop() {
    while(active) {
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderClear( renderer );
        for(auto & p : players) {
            drawPlayerRect(p);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(view);
    SDL_Quit();
}

void GameWindow::stop() {
    active = false;
}

void GameWindow::getGameState(GameStatePacket *game_state_packet) {
    players = game_state_packet->getPlayers();
}

void GameWindow::drawPlayerRect(std::shared_ptr<PlayerModel> &player) {
    decidePlayerRectColor(player);
    SDL_Rect r = setUpPlayerRect(player);
    SDL_RenderFillRect( renderer, &r );
}

void GameWindow::decidePlayerRectColor(std::shared_ptr<PlayerModel> &player) {
    if(player->is_enemy)
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    else
        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
}

SDL_Rect GameWindow::setUpPlayerRect(std::shared_ptr<PlayerModel> &player) {
    SDL_Rect rect;
    rect.x = player->pos_x;
    rect.y = player->pos_y;
    rect.w = 10;
    rect.h = 10;
    return rect;
}
