#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "shield.h"

namespace game {

    //Constructor
    Shield::Shield(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* parent)
        : GameObject(position, texture, num_elements, true, 0.5) {
        parent_ = parent;
        scale_ = SHIELD_SCALE;
    }


    void Shield::Update(double delta_time, double current_time) {

        // Update Shield position_ directly so that it's always centered on the player
        velocity_ = parent_->GetVelocity();
        GameObject::Update(delta_time, current_time);
    }
    bool Shield::ValidCollision(GameObject* other_game_object, double deltatime) {
        return false;
    }
    bool Shield::HandleCollision(GameObject* other_game_object, double deltatime) {
        return true;
    }
} // namespace game
