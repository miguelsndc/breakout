#ifndef GAME_H
#define GAME_H

#include <glad.h>
#include <glfw3.h>

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
    Game(unsigned int Width, unsigned int Height);
    ~Game();
    void init();
    void process_input(float dt);
    void update(float dt);
    void render();
};

#endif