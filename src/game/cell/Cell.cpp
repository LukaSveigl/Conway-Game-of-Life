/**
 * @file Cell.cpp
 * @author Luka Šveigl (lukasveigl2708@gmail.com)
 * @brief The file that holds the implementation of the Cell class, which is the base building block of the game. 
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Cell.hpp"

#define MAX_COLOR_VALUE 255
#define MIN_COLOR_VALUE 0
#define GRAY_COLOR_VALUE 51
#define CELL_DIMENSION 32

/**
 * @brief Construct a new Cell object.
 * 
 */
Cell::Cell() {
    this->m_is_alive = false;
}

/**
 * @brief Construct a new Cell object.
 * 
 * @param renderer A pointer to the SDL renderer.
 * @param x The column of the cell.
 * @param y The row of the cell.
 */
Cell::Cell(SDL_Renderer *renderer, int x, int y) : 
    m_x{x}, 
    m_y{y}, 
    m_renderer{renderer} 
{
    this->m_rect.x = x * CELL_DIMENSION;
    this->m_rect.y = y * CELL_DIMENSION;
    this->m_rect.w = CELL_DIMENSION;
    this->m_rect.h = CELL_DIMENSION;

    this->m_is_alive = false;
    this->m_living_neighbours = 0;
}

/**
 * @brief Destroy the Cell object.
 * 
 */
Cell::~Cell() {
}

/**
 * @brief Update the cell's state based on it's neighbours.
 * 
 */
void Cell::update() {
    if (!this->m_is_alive) {
        // Any dead cell with exactly 3 live neighbors becomes a live cell, as if by reproduction.
        if (this->m_living_neighbours == 3) {
            this->live();
        }
    }
    else {
        // Any live cell with fewer than 2 live neighbors dies, as if by underpopulation.
        if (this->m_living_neighbours < 2 ) {
            this->kill();
        }
        // Any live cell with more than three live neighbours dies, as if by overpopulation.
        if (this->m_living_neighbours > 3) {
            this->kill();
        }
        // Any live cell with 2 or 3 live neighbours lives on to the next generation.
    }

    this->m_living_neighbours = 0;
}

/**
 * @brief Render the cell.
 * 
 */
void Cell::render() {
    if (this->m_is_alive) {
        SDL_SetRenderDrawColor(
            this->m_renderer, 
            MIN_COLOR_VALUE, 
            MAX_COLOR_VALUE, 
            MIN_COLOR_VALUE, 
            MAX_COLOR_VALUE
        );
    }
    else {
        SDL_SetRenderDrawColor(
            this->m_renderer, 
            MIN_COLOR_VALUE, 
            MIN_COLOR_VALUE, 
            MIN_COLOR_VALUE, 
            MAX_COLOR_VALUE
        );
    }
    SDL_RenderFillRect(this->m_renderer, &this->m_rect);

    // Draw outline of cell.
    SDL_SetRenderDrawColor(
        this->m_renderer, 
        GRAY_COLOR_VALUE, 
        GRAY_COLOR_VALUE, 
        GRAY_COLOR_VALUE, 
        MAX_COLOR_VALUE
    );
    SDL_RenderDrawRect(this->m_renderer, &this->m_rect);
}

/**
 * @brief Count this cell's living neighbours.
 * 
 */
void Cell::count_neighbours() {
    for (Cell *neighbor : this->m_neighbours) {
        if (neighbor != nullptr) {
            if (neighbor->is_alive()) {
                this->m_living_neighbours++;
            }
        }
    }
}

/**
 * @brief Set the neighbours of this cell.
 * 
 * @param neighbours An array of the eight neighbours.
 */
void Cell::set_neighbours(Cell *neighbours[8]) {
    for (size_t i = 0; i < 8; i++) {
        this->m_neighbours[i] = neighbours[i];
    }
}

/**
 * @brief Kill the cell.
 * 
 */
void Cell::kill() {
    this->m_is_alive = false;
}

/**
 * @brief Reanimate the cell.
 * 
 */
void Cell::live() {
    this->m_is_alive = true;
}

/**
 * @brief Tell if the cell is alive.
 * 
 * @return true If the cell is alive,
 * @return false otherwise.
 */
bool Cell::is_alive() {
    return this->m_is_alive;
}