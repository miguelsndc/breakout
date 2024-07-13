#ifndef GAME_H
#define GAME_H

#include <glad.h>
#include <glfw3.h>

#include <vector>

#include "game_level.h"
#include "game_object.h"

enum GameState {
    GAME_ACTIVE,
    GAME_WIN,
    GAME_MENU
};

class Game {
   public:
    GameState state;
    bool keys[1024];
    unsigned int width, height;
    std::vector<GameLevel> levels;
    unsigned int level;

    Game(unsigned int Width, unsigned int Height);
    ~Game();
    void init();
    void process_input(float dt);
    void update(float dt);
    void render();
};

#endif