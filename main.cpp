/**
 * @file main.cpp
 * @author Luka Šveigl (lukasveigl2708@gmail.com)
 * @brief The entry point of the game.
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "src/game/Game.hpp"

#include <iostream>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define FULLSCREEN true
#define GAME_NAME "Life"

int main(int argc, char* argv[]) {
    Game game;
    int status = game.init(
        GAME_NAME, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        FULLSCREEN
    );

    if (status) {
        std::cerr << "The game could not be initialized." << std::endl;
        return 1;
    }
    game.run();
    game.cleanup();

    return 0;
}