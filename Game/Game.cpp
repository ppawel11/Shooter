//
// Created by pawel on 29.04.2020.
//

#include "Game.h"

Game::Game(std::shared_ptr<Controller> contr){
    running = false;
    finished = false;
    commands_counter = 0;
    player_id = -1;
    over.lock();
    ready.lock();
    controller = contr;
    going = STOP;
    current_id = 0;
}

void Game::getUpdate(std::string &update){
    std::shared_ptr<Packet> received = packet_factory.createPacket(update);
    received->beHandled(this);
}

void Game::handle(InitPacket *init_packet) {
    player_id = init_packet->getClientId();
    ready.unlock();
}

void Game::handle(StartingPacket *start_packet) {
    start();
    controller->initWindow();
}

void Game::handle(GameStatePacket *game_state_packet) {
    if(game_state_packet->getStateId() > current_id) {
        current_id = game_state_packet->getStateId();
        std::vector<std::shared_ptr<PlayerModel>> players = game_state_packet->getPlayers();
        for(auto p : players){
            if(p->id == player_id)
                p->is_enemy = false;
        }
        controller->updateWindow(game_state_packet);
    }
}

void Game::start() {
    running = true;
    main_thread = std::thread(&Game::getKeyboardCommands, this);
    main_thread.detach();
}

void Game::stop(){
    running = false;
    finished = true;
    controller->deactivateWindow();
    addCommand(std::string(protocol::end_of_game));
    over.unlock();
}

void Game::disconnect() {
    std::cout<<"unexpected disconnection"<<std::endl;
    finished = true;
    if(running)
        stop();
    over.unlock();
}

bool Game::isRunning() {
    return running;
}

std::string Game::getNextCommand() {
    return commands_to_send.pop();
}

bool Game::isFinished() {
    return finished;
}

const int Game::getGameId() {
    ready.lock();
    return player_id;
}

void Game::getKeyboardCommands() {
    bool a_pressed, w_pressed, d_pressed, s_pressed;
    int vertical, horizontal;

    while(running){
        vertical = 1;
        horizontal = 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            stop();
            break;
        }
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
        direction to_go = directions_board[vertical][horizontal];
        if(to_go != STOP || to_go != going) {
            addCommand(directions_board[vertical][horizontal]);
            going = to_go;
        }
        std::this_thread::yield();

    }
}

void Game::addCommand(direction command) {
    std::string command_str = "T";
    command_str.push_back((char)(unsigned int)command);
    commands_to_send.push(command_str);
}

void Game::waitUntilOver() {
    over.lock();
}

void Game::addCommand(std::string command) {
    commands_to_send.push(command);
}
