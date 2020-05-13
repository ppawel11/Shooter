cmake_minimum_required(VERSION 3.16)
project(tin)
list(APPEND CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")
find_package(SFML COMPONENTS graphics audio REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(tin ${SDL2_INCLUDE_DIRS})


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(tin main.cpp
        Game/Game.cpp Game/Game.h
        Connection/Connection.cpp Connection/Connection.h
        Connection/UdpConnection.cpp Connection/UdpConnection.h
        Connection/TcpConnection.cpp Connection/TcpConnection.h
        common.h Game/GameManager.cpp Game/GameManager.h
        Connection/TcpHandler.cpp Connection/TcpHandler.h
        Connection/UdpHandler.cpp Connection/UdpHandler.h
        Abstract/BlockingQueue.h
        View/GameWindow/GameWindow.cpp View/GameWindow/GameWindow.h
        Model/PlayerModel.h Controller/Controller.cpp Controller/Controller.h Abstract/PacketsFactory.cpp Abstract/PacketsFactory.h Connection/Packets/Packet.h Connection/Packets/InitPacket.cpp Connection/Packets/InitPacket.h Connection/Packets/GameStatePacket.cpp Connection/Packets/GameStatePacket.h Connection/Packets/StartingPacket.cpp Connection/Packets/StartingPacket.h)

target_link_libraries(tin ${SDL2_LIBRARIES})
target_link_libraries(tin sfml-graphics sfml-window sfml-system)
