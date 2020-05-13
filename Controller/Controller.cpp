//
// Created by pawel on 11.05.2020.
//

#include "Controller.h"

Controller::Controller() {

}

void Controller::attachGame(std::shared_ptr <Game> obs) {
    game_observer = obs;
}

void Controller::attachGameWindow(std::shared_ptr <GameWindow> obs) {
    game_window_observer = obs;
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
