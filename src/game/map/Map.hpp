/**
 * @file Map.hpp
 * @author Luka Šveigl (lukasveigl2708@gmail.com)
 * @brief The file that holds the definition of the Map class, which is a container for all of the cells. 
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef Map_hpp
#define Map_hpp

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "../cell/Cell.hpp"

#include <iostream>

#define MAP_WIDTH 32
#define MAP_HEIGHT 24

/**
 * @brief The different states the game can be in.
 * 
 */
enum GameState {
    SETUP_STATE,
    SIMULATING,
    PAUSED
};

/**
 * @brief The class that represents the map of cells.
 * 
 */
class Map {
private:
    int m_width;
    int m_height;
    
    GameState m_state;
    Cell m_map[MAP_WIDTH][MAP_HEIGHT];

    SDL_Renderer *m_renderer;
public:
    /**
     * @brief Construct a new Map object.
     * 
     */
    Map();
    /**
     * @brief Construct a new Map object.
     * 
     * @param width The screen width.
     * @param height The screen height.
     * @param renderer A pointer to the SDL renderer.
     */
    Map(int width, int height, SDL_Renderer *renderer);
    /**
     * @brief Destroy the Map object.
     * 
     */
    ~Map();

    /**
     * @brief Update every cell in the game.
     * 
     */
    void update();
    /**
     * @brief Render every cell in the game.
     * 
     */
    void render();

    /**
     * @brief Return a pointer to the cell at the x, y position.
     * 
     * @param x The column of the cell.
     * @param y The row of the cell.
     * @return Cell* A pointer to the cell.
     */
    Cell *tile_at(int x, int y);

    /**
     * @brief Start the simulation.
     * 
     */
    void start();
    /**
     * @brief Reset the simulation.
     * 
     */
    void reset();
    /**
     * @brief Pause the simulation. Can be undone by the start() method.
     * 
     */
    void pause();

    /**
     * @brief Get the current game state.
     * 
     * @return GameState The current game state.
     */
    GameState get_game_state();
};

#endif /*Map_hpp*/