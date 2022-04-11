#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <cstdlib>
#include "enemy_game_object.h"
#include "collision.h"
#include "bullet.h"
namespace game {

    /*
        EnemyGameObject inherits from GameObject
        It overrides GameObject's update method, so that you can check for input to change the velocity of the enemy
    */
    EnemyGameObject::EnemyGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GLuint hurt_texture, int damage, int health)
        : GameObject(position, texture, num_elements, true, 0.5) {
        default_texture_ = texture;
        hurt_texture_ = hurt_texture;
        damage_ = damage;
        name_ = enemy;
    }

    bool EnemyGameObject::ValidCollision(GameObject* other_game_object, double deltatime)
    {
        switch (other_game_object->GetName()) {
        case player:
            return Collision::CircleCircleCollision(other_game_object, position_, radius_);

        default:
            return false;
        }
    }
    bool EnemyGameObject::HandleCollision(GameObject* other_game_object, double deltatime)
    {
        Bullet* b;
        switch (other_game_object->GetName()) {
        case player:
            dead_ = true;
            break;

        case bullet:
            b = dynamic_cast<Bullet*>(other_game_object);
            if (b->GetFirer() == player) {
                TakeDamage(1, deltatime);
            }
            break;
        case missile:
            TakeDamage(3, deltatime);
            break;
        }

        return true;
    }
    void EnemyGameObject::TakeDamage(int amt, double deltatime) {
        health_ -= amt;
        time_since_hit_ = deltatime;
        texture_ = hurt_texture_;
        if (health_ == 0) {
            dead_ = true;
        }
    }

} // namespace game
