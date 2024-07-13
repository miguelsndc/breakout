#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad.h>

#include <glm/glm.hpp>

#include "sprite_renderer.h"
#include "texture.h"

class GameObject {
   public:
    glm::vec2 position, velocity, size;
    glm::vec3 color;
    float rotation;
    bool is_solid;
    bool destroyed;
    Texture2D sprite;

    GameObject();
    GameObject(glm::vec2 ppos,
               glm::vec2 psize,
               Texture2D psprite,
               glm::vec3 pcolor = glm::vec3(1.0f),
               glm::vec2 pvel = glm::vec2(0.0f));
    virtual void draw(SpriteRenderer &renderer);
};

#endif