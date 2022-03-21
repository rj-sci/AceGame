#include "powerup.h"
#include "collision.h"

namespace game {
    PowerUp::PowerUp(const glm::vec3& position, GLuint texture, GLint num_elements,PUpType type) :
        GameObject(position, texture, num_elements, true, 0.5, powerup) {
        scale_ = POWERUP_SCALE;
        type_ = type;
    }

    void PowerUp::Update(double delta_time) {
        GameObject::Update(delta_time);
    }

    bool PowerUp::ValidCollision(GameObject* other_game_object, double deltatime) {
        switch (other_game_object->GetName()) {
        case player:
            return Collision::CicleCircleCollision(other_game_object, position_, radius_);
        }
    }
    bool PowerUp::HandleCollision(GameObject* other_game_object, double deltatime) {
        switch (other_game_object->GetName()) {
        case player:
            PlayerGameObject* ply = (PlayerGameObject*)other_game_object;
            ply->SetPowerUp(type_);
            dead_ = true;
            return true;
        }
        return false;
    }
}