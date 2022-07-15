/**
 * @file Game.cpp
 * @author Luka Šveigl (lukasveigl2708@gmail.com)
 * @brief The file that holds the implementation of the main Game class. 
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Game.hpp"

#define MAX_COLOR_VALUE 255
#define DEFAULT_FLAGS 0
#define DEFAULT_INDEX -1
#define CELL_DIMENSION 32

#define LOW_FPS 4
#define HIGH_FPS 60
#define SIMULATING 1

/**
 * @brief Construct a new Game object.
 * 
 */
Game::Game() {
    this->m_window = nullptr;
    this->m_renderer = nullptr;
}

/**
 * @brief Destroy the Game object.
 * 
 */
Game::~Game() {
    // Deletion unnecessary, SDL components are destroyed during cleanup.
    std::cout << "Game finished." << std::endl;
}

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
int Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = DEFAULT_FLAGS;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL2: " << SDL_GetError() << std::endl;
        this->m_is_running = false;
        return 1;
    }

    this->m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (this->m_window) {
        std::cout << "SDL Window created." << std::endl;
    }

    this->m_renderer = SDL_CreateRenderer(this->m_window, DEFAULT_INDEX, DEFAULT_FLAGS);
    if (this->m_renderer) {
        SDL_SetRenderDrawColor(
            this->m_renderer, 
            MAX_COLOR_VALUE, 
            MAX_COLOR_VALUE, 
            MAX_COLOR_VALUE, 
            MAX_COLOR_VALUE
        );
        std::cout << "SDL Renderer created." << std::endl;
    }

    this->m_is_running = true;
    this->m_map = Map(width, height, this->m_renderer);

    return 0;
}

/**
 * @brief Clean up the SDL components.
 * 
 */
void Game::cleanup() {
    SDL_DestroyWindow(this->m_window);
    SDL_DestroyRenderer(this->m_renderer);
    SDL_Quit();
    std::cout << "Cleanup complete." << std::endl;
}

/**
 * @brief Update the game state.
 * 
 */
void Game::update() {
    this->m_map.update();
}

/**
 * @brief Render the current game state.
 * 
 */
void Game::render() {
    this->m_map.render();
    SDL_RenderPresent(this->m_renderer);
}

/**
 * @brief Handle events that affect the game.
 * 
 */
void Game::handle_events() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            this->m_is_running = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_s:
                    std::cout << "Starting." << std::endl;
                    this->m_map.start();
                    break;
                case SDLK_r:
                    std::cout << "Resetting." << std::endl;
                    this->m_map.reset();
                    break;
                case SDLK_p:
                    std::cout << "Pausing." << std::endl;
                    this->m_map.pause();
                    break;
                case SDLK_ESCAPE:
                    this->m_is_running = false;
                    break;
            } 
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int x = floor(event.button.x / CELL_DIMENSION);
                int y = floor(event.button.y / CELL_DIMENSION);
                if (x < 32 && y < 32 && x >= 0 && y >= 0) {
                    this->m_map.tile_at(x, y)->live();
                }
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                int x = floor(event.button.x / CELL_DIMENSION);
                int y = floor(event.button.y / CELL_DIMENSION);
                if (x < 32 && y < 32 && x >= 0 && y >= 0) {
                    this->m_map.tile_at(x, y)->kill();
                }
            }
            break;
    }
}

/**
 * @brief Continually executes the game.
 * 
 */
void Game::run() {
    int FPS = LOW_FPS;
    int frame_delay = 1000 / FPS;

    Uint32 frame_start;
    int frame_time;

    int state = 0;

    while (this->is_running()) {
        frame_start = SDL_GetTicks();

        this->handle_events();
        this->update();
        this->render();
        
        state = this->m_map.get_game_state();

        if (state == SIMULATING) {
            FPS = LOW_FPS;
        }
        else {
            FPS = HIGH_FPS;
        }
        frame_delay = 1000 / FPS;

        frame_time = SDL_GetTicks() - frame_start;
        // Make sure that the game runs at the specified FPS.
        if (frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }
    }
}

/**
 * @brief Tell if the game is running.
 * 
 * @return true If the game is running,
 * @return false otherwise.
 */
bool Game::is_running() {
    return this->m_is_running;
}