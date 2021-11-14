cmake_minimum_required(VERSION 3.20)
project(CLion)

set(CMAKE_CXX_STANDARD 14)

include_directories(Cards)
include_directories(Map)
include_directories(Orders)
include_directories(Player)

add_executable(CLion
        Cards/Cards.cpp
        Cards/Cards.h
        Map/Map.cpp
        Map/Map.h
        Orders/Orders.cpp
        Orders/Orders.h
        Player/Player.cpp
        Player/Player.h
        GameEngine/GameEngine.cpp
        GameEngine/GameEngine.h
        GameEngine/GameEngineDriver.cpp
        Orders/LoggingObserver.h Orders/LoggingObserver.cpp)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/solar.map
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
