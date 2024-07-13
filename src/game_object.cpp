#include "game_object.h"

GameObject::GameObject() : position(0.0f, 0.0f),
                           velocity(0.0f),
                           size(1.0f, 1.0f),
                           color(1.0f),
                           rotation(1.0f),
                           is_solid(false),
                           destroyed(false),
                           sprite()

{
}

GameObject::GameObject(
    glm::vec2 ppos,
    glm::vec2 psize,
    Texture2D psprite,
    glm::vec3 pcolor,
    glm::vec2 pvel) : position(ppos),
                      velocity(pvel),
                      size(psize),
                      color(pcolor),
                      rotation(0.0f),
                      is_solid(false),
                      destroyed(false),
                      sprite(psprite) {
}

void GameObject::draw(SpriteRenderer &renderer) {
    renderer.draw(this->sprite, this->position, this->size, this->rotation, this->color);
}