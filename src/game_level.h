#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <glad.h>

#include <glm/glm.hpp>
#include <vector>

#include "game_object.h"
#include "sprite_renderer.h"

class GameLevel {
   private:
    void init(std::vector<std::vector<unsigned int>> tile_data, unsigned int level_width, unsigned int level_height);

   public:
    std::vector<GameObject> bricks;
    GameLevel() {}
    void load(const char* file, unsigned int level_width, unsigned int level_height);
    void draw(SpriteRenderer& renderer);
    // completed means all breakable tiles are gone
    bool is_completed();
};

#endif