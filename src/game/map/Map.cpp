/**
 * @file Map.cpp
 * @author Luka Šveigl (lukasveigl2708@gmail.com)
 * @brief The file that holds the implementation of the Map class, which is a container for all of the cells. 
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Map.hpp"

/**
 * @brief Construct a new Map object.
 * 
 */
Map::Map() {

}

/**
 * @brief Construct a new Map object.
 * 
 * @param width The screen width.
 * @param height The screen height.
 * @param renderer A pointer to the SDL renderer.
 */
Map::Map(int width, int height, SDL_Renderer *renderer) : 
    m_width{width}, 
    m_height{height}, 
    m_renderer{renderer} 
{
    for (size_t x = 0; x < MAP_WIDTH; x++) {
        for (size_t y = 0; y < MAP_HEIGHT; y++) {
            this->m_map[x][y] = Cell(renderer, x, y);
        }
    }

    this->m_state = GameState::SETUP_STATE;
}

/**
 * @brief Destroy the Map object.
 * 
 */
Map::~Map() {

}

/**
 * @brief Update every cell in the game.
 * 
 */
void Map::update() {
    if (this->m_state == GameState::SIMULATING) {
        // The neighbours have to be counted first for all cells, as otherwise
        // updating one cell might have unforeseen consequences on other cells.
        for (size_t x = 0; x < MAP_WIDTH; x++) {
            for (size_t y = 0; y < MAP_HEIGHT; y++) {
                this->m_map[x][y].count_neighbours();
            }
        }
        for (size_t x = 0; x < MAP_WIDTH; x++) {
            for (size_t y = 0; y < MAP_HEIGHT; y++) {
                this->m_map[x][y].update();
            }
        }
        std::cout << "Simulating." << std::endl;
    }
}

/**
 * @brief Render every cell in the game.
 * 
 */
void Map::render() {
    for (size_t x = 0; x < MAP_WIDTH; x++) {
        for (size_t y = 0; y < MAP_HEIGHT; y++) {
            this->m_map[x][y].render();
        }
    }
}

/**
 * @brief Return a pointer to the cell at the x, y position.
 * 
 * @param x The column of the cell.
 * @param y The row of the cell.
 * @return Cell* A pointer to the cell.
 */
Cell *Map::tile_at(int x, int y) {
    if (x < MAP_WIDTH && y < MAP_HEIGHT && x >= 0 && y >= 0) {
        return &this->m_map[x][y];
    }
    return nullptr;
}

/**
 * @brief Start the simulation.
 * 
 */
void Map::start() {
    this->m_state = GameState::SIMULATING;

    for (size_t x = 0; x < MAP_WIDTH; x++) {
        for (size_t y = 0; y < MAP_HEIGHT; y++) {
            Cell *neighbors[8] = {
                this->tile_at(x - 1, y - 1), // Get the 8 neighbors around the current cell, 
                this->tile_at(x    , y - 1), // which can either be pointers to a cell or nullptr
                this->tile_at(x + 1, y - 1), // in case the cell doesn't exist (edges).
                this->tile_at(x - 1, y),     // Indices go as follow:
                this->tile_at(x + 1, y),     // [x-1, y-1 ; x, y-1 ; x+1, y-1]
                this->tile_at(x - 1, y + 1), // [x-1, y   ; x, y   ; x+1, y  ]
                this->tile_at(x    , y + 1), // [x-1, y+1 ; x, y+1 ; x+1, y+1]
                this->tile_at(x + 1, y + 1)  //
            };
            this->m_map[x][y].set_neighbours(neighbors);
        }
    }
}

/**
 * @brief Reset the simulation.
 * 
 */
void Map::reset() {
    this->m_state = GameState::SETUP_STATE;

    for (size_t x = 0; x < MAP_WIDTH; x++) {
        for (size_t y = 0; y < MAP_HEIGHT; y++) {
            this->m_map[x][y].kill();
        }
    }
}

/**
 * @brief Pause the simulation. Can be undone by the start() method.
 * 
 */
void Map::pause() {
    this->m_state = GameState::PAUSED;
}

/**
 * @brief Get the current game state.
 * 
 * @return GameState The current game state.
 */
GameState Map::get_game_state() {
    return this->m_state;
}
