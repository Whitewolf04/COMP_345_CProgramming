cmake_minimum_required(VERSION 3.20)
project(Game_Engine)

set(CMAKE_CXX_STANDARD 14)

add_executable(Game_Engine GameEngine.cpp GameEngine.h GameEngineDriver.cpp Cards.h Cards.cpp Map.h Map.cpp Orders.h Orders.cpp Player.h Player.cpp LoggingObserver.cpp LoggingObserver.h)

file(COPY solar.map
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})