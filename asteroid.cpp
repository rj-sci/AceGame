#include "asteroid.h"
#include "collision.h"

namespace game {
    Asteroid::Asteroid(const glm::vec3& position, GLuint texture, GLint num_elements, GLuint dest_texture):
    EnemyGameObject(position, texture, num_elements, dest_texture, asteroid, ASTEROID_DMG) {
        scale_ = ASTEROID_SCALE;
    }

    // Update function for moving the player object around
    void Asteroid::Update(double delta_time) {
        EnemyGameObject::Update(delta_time);
    }
    bool Asteroid::ValidCollision(GameObject* other_game_object, double deltatime) {
        switch (other_game_object->GetName()) {
        case player:
            return Collision::CicleCircleCollision(other_game_object, position_, radius_);
        }
    }
    bool Asteroid::HandleCollision(GameObject* other_game_object, double deltatime) {
        return true;
    }
}