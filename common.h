//
// Created by pawel on 29.04.2020.
//

#ifndef TIN_COMMON_H
#define TIN_COMMON_H

#include <string>

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
    static const char * end_of_game = {"EOG"};
    static const char * start = {"start"};
    static const char * stop = {"STOP"};
}

#endif //TIN_COMMON_H
