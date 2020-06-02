//
// Created by pawel on 29.04.2020.
//

#ifndef TIN_COMMON_H
#define TIN_COMMON_H

#include <string>
#include <vector>

enum direction{STOP, UP, RIGHT_UP, RIGHT, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT, LEFT_UP};

static const direction directions_board[3][3] = {{LEFT_UP, UP, RIGHT_UP},
                                                 {LEFT, STOP, RIGHT},
                                                 {LEFT_DOWN, DOWN, RIGHT_DOWN}}; //vertical, horizontal

namespace server{
    static int tcp_port = 8888;
    static int udp_port = 8888;
    static const char * ip = "127.0.0.1";
}

namespace client{
    static const int port = 9000;
    static const char * ip = "127.0.0.1";
}

namespace protocol{
    static const int max_size = 1024;
    static const char * alive = {"alive"};
    static const int alive_len = 5;
    static const char * end_of_game = {"EOG"};
    static const char * stop = {"stop"};
    static const char starting_packet_mark = 'S';
    static const char init_packet_mark = 'X';
    static const char game_state_packet_mark = 'Y';
    static const char shoot_packet_mark = 'Z';
    static const char move_packet_mark = 'T';
    static const char end_of_game_mark = 'E';
}

namespace view{
    static const int window_height = 600;
    static const int window_width = 600;
    static const int player_size = 30;
    static const int bullet_size = 10;
}

#endif //TIN_COMMON_H
