/**
 * @file Cell.hpp
 * @author Luka Šveigl (lukasveigl2708@gmail.com)
 * @brief The file that holds the definition of the Cell class, which is the base building block of the game. 
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef Cell_hpp
#define Cell_hpp

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <iostream>

/**
 * @brief The class that represents a single cell in the game.
 * 
 */
class Cell {
private:
    int m_x;
    int m_y;

    bool m_is_alive;
    int m_living_neighbours;

    Cell *m_neighbours[8];

    SDL_Rect m_rect;
    SDL_Renderer *m_renderer;
public:
    /**
     * @brief Construct a new Cell object.
     * 
     */
    Cell();
    /**
     * @brief Construct a new Cell object.
     * 
     * @param renderer A pointer to the SDL renderer.
     * @param x The column of the cell.
     * @param y The row of the cell.
     */
    Cell(SDL_Renderer *renderer, int x, int y);
    /**
     * @brief Destroy the Cell object.
     * 
     */
    ~Cell();

    /**
     * @brief Update the cell's state based on it's neighbours.
     * 
     */
    void update();
    /**
     * @brief Render the cell.
     * 
     */
    void render();

    /**
     * @brief Count this cell's living neighbours.
     * 
     */
    void count_neighbours();
    /**
     * @brief Set the neighbours of this cell.
     * 
     * @param neighbours An array of the eight neighbours.
     */
    void set_neighbours(Cell *neighbours[8]);

    /**
     * @brief Kill the cell.
     * 
     */
    void kill();
    /**
     * @brief Reanimate the cell.
     * 
     */
    void live();
    /**
     * @brief Tell if the cell is alive.
     * 
     * @return true If the cell is alive,
     * @return false otherwise.
     */
    bool is_alive();
};

#endif /*Cell_hpp*/