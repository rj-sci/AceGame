#pragma once
#include "enemy_game_object.h"
#include "powerup.h"
#include "defs.h"
#include "collision.h"

namespace game {

    // Inherits from GameObject
    class SaucerGameObject : public EnemyGameObject {

    public:
        SaucerGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject *p, GLuint laserTex, GLuint hurt_tex, float radius);

        // Update function for moving the player object around
        void Update(double delta_tim, double current_time) override;

        void Render(Shader& shader, glm::mat4 view_matrix, double current_time) override;
        //getters
       void TakeDamage(int amt, double deltatime);


       
        //setters
    private:
        GameObject* target_;
        GameObject* laser_;
        int health_;

         
    }; // class PlayerGameObject

} // namespace game

