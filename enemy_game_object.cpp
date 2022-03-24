#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <cstdlib>
#include "enemy_game_object.h"

namespace game {

    /*
        EnemyGameObject inherits from GameObject
        It overrides GameObject's update method, so that you can check for input to change the velocity of the enemy
    */
    EnemyGameObject::EnemyGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GLuint dest_texture, Name name,int damage)
        : GameObject(position, texture, num_elements, true, 0.25, name) {
        acceleration_ = 0;
        dest_texture_ = dest_texture;
        dead_ = false;
        damage_ = damage;
        
    }
} // namespace game
