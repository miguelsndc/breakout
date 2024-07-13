#include "game.h"

#include <glm/glm.hpp>
#include <string>

#include "logger.hpp"
#include "resource_manager.h"
#include "sprite_renderer.h"

SpriteRenderer *renderer;

Game::Game(unsigned int width, unsigned int height)
    : state(GAME_ACTIVE), keys(), width(width), height(height), levels(0) {
}

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY = 500.0F;

GameObject *player;

void Game::init() {
    // setup shaders
    ResourceManager::load_shader("src\\shaders\\sprite.vert", "src\\shaders\\sprite.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
                                      static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

    ResourceManager::get_shader("sprite").use().set_integer("image", 0);
    ResourceManager::get_shader("sprite").use().set_matrix4("projection", projection);
    renderer = new SpriteRenderer(ResourceManager::get_shader("sprite"));

    // setup textures
    ResourceManager::load_texture("src\\textures\\background.jpg", false, "background");
    ResourceManager::load_texture("src\\textures\\awesomeface.png", true, "face");
    ResourceManager::load_texture("src\\textures\\block.png", false, "block");
    ResourceManager::load_texture("src\\textures\\block_solid.png", false, "block_solid");

    // setup levels
    GameLevel one, two, three, four;
    one.load("src\\levels\\one.lvl", this->width, this->height / 2);
    two.load("src\\levels\\two.lvl", this->width, this->height / 2);
    three.load("src\\levels\\three.lvl", this->width, this->height / 2);
    four.load("src\\levels\\four.lvl", this->width, this->height / 2);

    this->levels.push_back(one);
    this->levels.push_back(two);
    this->levels.push_back(three);
    this->levels.push_back(four);

    // setup player paddle
    ResourceManager::load_texture("src\\textures\\paddle.png", true, "paddle");
    glm::vec2 player_pos = glm::vec2(
        this->width / 2.0f - PLAYER_SIZE.x / 2.0f,
        this->height - PLAYER_SIZE.y);

    player = new GameObject(player_pos, PLAYER_SIZE, ResourceManager::get_texture("paddle"));
}

void Game::update(float dt) {
}

void Game::process_input(float dt) {
    if (this->state == GAME_ACTIVE) {
        float velocity = PLAYER_VELOCITY * dt;
        if (this->keys[GLFW_KEY_A]) {
            if (player->position.x >= 0.0f) {
                player->position.x -= velocity;
            }
        }
        if (this->keys[GLFW_KEY_D]) {
            if (player->position.x <= this->width - player->size.x) {
                player->position.x += velocity;
            }
        }
    }
}

void Game::render() {
    if (this->state == GAME_ACTIVE) {
        renderer->draw(ResourceManager::get_texture("background"),
                       glm::vec2(0.0f), glm::vec2(this->width, this->height), 0.0f);

        this->levels[this->level].draw(*renderer);
        player->draw(*renderer);
    }
}

Game::~Game() {
    delete renderer;
    delete player;
}