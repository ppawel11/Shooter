//
// Created by qt on 11.05.2020.
//

#include "GameWindow.h"
#include <thread>
#include <iostream>
#include <cmath>
#include <utility>

GameWindow::GameWindow(std::shared_ptr<Controller> contr) {
    controller = std::move(contr);
    view = nullptr;
    renderer = nullptr;
    active = false;
    last_position = {-1, -1};
    ready.lock();
}

void GameWindow::start() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("sdl could not initialize");
    active = true;
    view = SDL_CreateWindow("Shooter X", 500, 100, view::window_width, view::window_height, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer( view, -1, SDL_RENDERER_ACCELERATED);
    ready.unlock();
    loop();
}

void GameWindow::loop() {
    int mouse_x, mouse_y;
    SDL_Event e;
    while(active) {
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&mouse_x, &mouse_y);
                shoot(mouse_x, mouse_y);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            controller->finish();

        direction to_go = getDirectionInput();
        controller->move(to_go);

        clearScreen();
        drawComponents();
        SDL_RenderPresent(renderer);

//        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    SDL_DestroyWindow(view);
    SDL_Quit();
}

void GameWindow::stop() {
    active = false;
}

void GameWindow::getGameState(GameStatePacket *game_state_packet) {
    players = game_state_packet->getPlayers();
    bullets = game_state_packet->getBullets();
    updateLastPosition();
}

void GameWindow::drawPlayerRect(std::shared_ptr<PlayerModel> &player) {
    decidePlayerRectColor(player);
    SDL_Rect r = setUpPlayerRect(player);
    SDL_RenderFillRect( renderer, &r );
}

void GameWindow::drawBulletRect(std::shared_ptr<BulletModel> &bullet) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect r = setUpBulletRect(bullet);
    SDL_RenderFillRect(renderer, &r);
}

void GameWindow::decidePlayerRectColor(std::shared_ptr<PlayerModel> &player) {
    if(player->is_enemy)
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    else
        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
}

SDL_Rect GameWindow::setUpPlayerRect(std::shared_ptr<PlayerModel> &player) {
    SDL_Rect rect;
    rect.x = player->pos_x - view::player_size / 2;
    rect.y = player->pos_y - view::player_size / 2;
    rect.w = view::player_size;
    rect.h = view::player_size;
    return rect;
}

SDL_Rect GameWindow::setUpBulletRect(std::shared_ptr<BulletModel> &bullet) {
    SDL_Rect rect;
    rect.x = bullet->pos_x-view::bullet_size/2;
    rect.y = bullet->pos_y-view::bullet_size/2;
    rect.w = view::bullet_size;
    rect.h = view::bullet_size;
    return rect;
}

void GameWindow::updateLastPosition() {
    for(auto & p : players) {
        if(!p->is_enemy) {
            last_position[0] = p->pos_x;
            last_position[1] = p->pos_y;
            break;
        }
    }
}

void GameWindow::shoot(int &x, int &y) {
    if (last_position[0] == -1)
        return;
    int delta_x = x - (int)last_position[0];
    int delta_y = (int)last_position[1] - y;
    int angle = 270 + (int)(180.0 * (atan2(delta_x, delta_y)/3.14));
    if (angle > 360)
        angle -= 360;
    controller->shoot(angle);
}

direction GameWindow::getDirectionInput() {
    bool a_pressed, w_pressed, d_pressed, s_pressed;
    int vertical = 1, horizontal = 1;

    a_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    w_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    d_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    s_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    if(a_pressed)
        horizontal -= 1;
    if(d_pressed)
        horizontal += 1;
    if(w_pressed)
        vertical -= 1;
    if(s_pressed)
        vertical += 1;

    return directions_board[vertical][horizontal];
}

void GameWindow::drawComponents() {
        for(auto & p : players)
            drawPlayerRect(p);
        for(auto & b : bullets)
            drawBulletRect(b);
}

void GameWindow::clearScreen() {
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );
}
