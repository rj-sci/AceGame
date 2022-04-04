#pragma once
#include "enemy_game_object.h"
#include "powerup.h"
#include "defs.h"
#include "collision.h"

namespace game {

    // Inherits from GameObject
    class SaucerGameObject : public GameObject {

    public:
        SaucerGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject *p, bool collidable, float radius, Name name);

        // Update function for moving the player object around
        void Update(double delta_time) override;

        void Render(Shader& shader, double current_time) override;
        //inherited virtual functions
       bool ValidCollision(GameObject* other_game_object, double deltatime);
       bool HandleCollision(GameObject* other_game_object, double deltatime);
        //getters

       
        //setters
    private:
        GameObject* target_;
         
    }; // class PlayerGameObject

} // namespace game

