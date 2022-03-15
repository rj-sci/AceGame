#include "asteroid.h"

namespace game {
    Asteroid::Asteroid(const glm::vec3& position, GLuint texture, GLint num_elements, GLuint dest_texture):
    EnemyGameObject(position, texture, num_elements, dest_texture, Name::Asteroid, ASTEROID_DMG) {
            
    }

    // Update function for moving the player object around
    void Asteroid::Update(double delta_time) {
        GameObject::Update(delta_time);
    }
    bool Asteroid::ValidCollision(GameObject* other_game_object, double deltatime) {
        if (other_game_object->GetName() == Name::Player) {
            return CCCollision(other_game_object);
        }
    }
    bool Asteroid::HandleCollision(GameObject* other_game_object, double deltatime) {
        return true;
    }
}