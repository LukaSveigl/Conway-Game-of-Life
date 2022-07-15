/**
 * @file Game.hpp
 * @author Luka Šveigl (lukasveigl2708@gmail.com)
 * @brief The file that holds the definition of the main Game class.
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef Game_hpp
#define Game_hpp

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <math.h>
#include <iostream>

#include "map/Map.hpp"

/**
 * @brief The main game class, which houses all of the components.
 * 
 */
class Game {
private:
    Map m_map;
    bool m_is_running;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

public:
    /**
     * @brief Construct a new Game object.
     * 
     */
    Game();
    /**
     * @brief Destroy the Game object.
     * 
     */
    ~Game();

    /**
     * @brief Initialize the SDL components such as window or renderer.
     * 
     * @param title The window title.
     * @param xpos The window horizontal position.
     * @param ypos The window vertical position.
     * @param width The window width.
     * @param height The window height.
     * @param fullscreen Flag that signifies if the window should be fullscreen.
     * @return int The exit code that signifies if the initialization was successful.
     */
    int init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    /**
     * @brief Continually executes the game.
     * 
     */
    void run();
    /**
     * @brief Clean up the SDL components.
     * 
     */
    void cleanup();

    /**
     * @brief Tell if the game is running.
     * 
     * @return true If the game is running,
     * @return false otherwise.
     */
    bool is_running();

private:
    /**
     * @brief Update the game state.
     * 
     */
    void update();
    /**
     * @brief Render the current game state.
     * 
     */
    void render();
   /**
    * @brief Handle events that affect the game.
    * 
    */
    void handle_events();
};

#endif /*Game_hpp*/