#include "tile.h"

namespace game {
    Tile::Tile(const glm::vec3& position, GLuint texture, GLint num_elements) 
        : GameObject(position, texture, num_elements, false, 0.5, Name::Tile) {}

    bool Tile::ValidCollision(GameObject * other_game_object, double deltatime) {
        return false;
    }
    bool Tile::HandleCollision(GameObject * other_game_object, double deltatime) {
        return false;
    }
}