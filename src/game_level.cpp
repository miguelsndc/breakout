#include "game_level.h"

#include <fstream>
#include <sstream>
#include <string>

#include "resource_manager.h"

void GameLevel::load(const char* file, unsigned int level_width, unsigned int level_height) {
    this->bricks.clear();
    unsigned int tile_code;
    std::string line;
    std::ifstream fstream(ResourceManager::get_path(file));
    std::vector<std::vector<unsigned int>> tiles;

    if (!fstream) return;

    while (std::getline(fstream, line)) {
        std::istringstream sstream(line);
        std::vector<unsigned int> row;
        while (sstream >> tile_code) {
            row.push_back(tile_code);
        }
        tiles.push_back(row);
    }

    if (tiles.size() > 0) {
        this->init(tiles, level_width, level_height);
    }
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tiles, unsigned int level_width, unsigned int level_height) {
    unsigned int height = tiles.size();
    unsigned int width = tiles[0].size();
    float unit_width = level_width / static_cast<float>(width);
    float unit_height = level_height / static_cast<float>(height);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            if (tiles[y][x] == 1) {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                GameObject object(
                    pos,
                    size,
                    ResourceManager::get_texture("block_solid"),
                    glm::vec3(0.8f, 0.8f, 0.7f));

                object.is_solid = true;
                this->bricks.push_back(object);
            } else if (tiles[y][x] > 1) {
                glm::vec3 color = glm::vec3(1.0f);
                switch (tiles[y][x]) {
                    case 2:
                        color = glm::vec3(0.2f, 0.6f, 1.0f);
                        break;
                    case 3:
                        color = glm::vec3(0.0f, 0.7f, 0.0f);
                        break;
                    case 4:
                        color = glm::vec3(0.8f, 0.8f, 0.4f);
                        break;
                    case 5:
                        color = glm::vec3(1.0f, 0.5f, 0.0f);
                        break;
                    default:
                        break;
                }

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                this->bricks.push_back(
                    GameObject(
                        pos, size, ResourceManager::get_texture("block"), color));
            }
        }
    }
}

void GameLevel::draw(SpriteRenderer& renderer) {
    for (GameObject& tile : this->bricks) {
        if (!tile.destroyed)
            tile.draw(renderer);
    }
}

bool GameLevel::is_completed() {
    for (GameObject& tile : this->bricks) {
        if (!tile.is_solid && !tile.destroyed) {
            return false;
        }
    }
    return true;
}