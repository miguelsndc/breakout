#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "texture.h"

class SpriteRenderer {
   public:
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();

    void draw(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.f, 10.f),
              float rotate = 0.f, glm::vec3(color) = glm::vec3(1.0f));

   private:
    unsigned int quadVAO;
    Shader shader;
    void init_render();
};

#endif