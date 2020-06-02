//
// Created by pawel on 11.05.2020.
//

#include "Controller.h"

#include <utility>

Controller::Controller() {

}

void Controller::attachGame(std::shared_ptr <Game> obs) {
    game_observer = std::move(obs);
}

void Controller::attachGameWindow(std::shared_ptr <GameWindow> obs) {
    game_window_observer = std::move(obs);
}

void Controller::updateWindow(GameStatePacket *game_state) {
    game_window_observer->getGameState(game_state);
}

void Controller::initWindow() {
    window_thread = std::thread(&GameWindow::start, game_window_observer);
    window_thread.detach();
}

void Controller::deactivateWindow() {
    game_window_observer->stop();
}

void Controller::shoot(int angle) {
    game_observer->shoot(angle);
}

void Controller::move(direction direction) {
    game_observer->move(direction);
}

void Controller::finish() {
    game_observer->stop();
}
