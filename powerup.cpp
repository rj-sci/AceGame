#include "powerup.h"
#include "collision.h"

namespace game {

    //Constructor for powerup
    PowerUp::PowerUp(const glm::vec3& position, GLuint texture, GLint num_elements,PUpType type) :
        GameObject(position, texture, num_elements, true, 0.5) {
        scale_ = POWERUP_SCALE;
        type_ = type;
        name_ = powerup;
    }

    //Update
    void PowerUp::Update(double delta_time, double current_time) {
        GameObject::Update(delta_time, current_time);
    }

    //Checks for valid collision with player and calls the appropriate functions
    bool PowerUp::ValidCollision(GameObject* other_game_object, double deltatime) {
        switch (other_game_object->GetName()) {
        case player:
            return Collision::CircleCircleCollision(other_game_object, position_, radius_);
            break;
        }
    }

    //Handles collision
    bool PowerUp::HandleCollision(GameObject* other_game_object, double deltatime) {
        switch (other_game_object->GetName()) {
        case player:
            dead_ = true;
            return true;
        }
        return false;
    }
}