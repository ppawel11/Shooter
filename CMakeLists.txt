cmake_minimum_required(VERSION 3.16)
project(tin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(tin main.cpp Game/Game.cpp Game/Game.h Connection/Connection.cpp Connection/Connection.h Connection/UdpConnection.cpp Connection/UdpConnection.h Connection/TcpConnection.cpp Connection/TcpConnection.h common.h Game/GameManager.cpp Game/GameManager.h Connection/TcpHandler.cpp Connection/TcpHandler.h Connection/UdpHandler.cpp Connection/UdpHandler.h Abstract/BlockingQueue.h)