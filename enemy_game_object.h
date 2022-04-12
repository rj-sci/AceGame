#pragma once
#include <string>
#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class EnemyGameObject : public GameObject {

    public:
        EnemyGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GLuint hurt_tex_,int damage, int health);
        //inherited virtual functions
        bool ValidCollision(GameObject* other_game_object, double deltatime);
        bool HandleCollision(GameObject* other_game_object, double deltatime);
        void TakeDamage(int amt, double deltatime);

        virtual void Update(double delta_time, double current_time);

        // Update function for moving the player object around
    protected:
        GLuint default_texture_;
        GLuint hurt_texture_;
        int damage_;
        int health_;
        double time_since_hit_;
    }; // class EnemyGameObject

} // namespace game