#include "game.h"

#include <glm/glm.hpp>

#include "resource_manager.h"
#include "sprite_renderer.h"

SpriteRenderer *renderer;

Game::Game(unsigned int width, unsigned int height)
    : state(GAME_ACTIVE), keys(), width(width), height(height) {
}

Game::~Game() {
    delete renderer;
}

void Game::init() {
    ResourceManager::load_shader("src\\shaders\\sprite.vert", "src\\shaders\\sprite.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
                                      static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::get_shader("sprite").use().set_integer("image", 0);
    ResourceManager::get_shader("sprite").use().set_matrix4("projection", projection);
    renderer = new SpriteRenderer(ResourceManager::get_shader("sprite"));
    ResourceManager::load_texture("src\\textures\\awesomeface.png", true, "face");
}

void Game::update(float dt) {
}

void Game::process_input(float dt) {
}

void Game::render() {
    renderer->draw(ResourceManager::get_texture("face"), glm::vec2(200.f, 200.f),
                   glm::vec2(300.f, 400.f), 45.f, glm::vec3(0.0f, 1.0f, 0.0f));
}