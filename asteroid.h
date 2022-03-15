#pragma once
#include <string>
#include "enemy_game_object.h"
#define ASTEROID_DMG 3
namespace game {

    // Inherits from EnemyGameObject
    class Asteroid : public EnemyGameObject {

    public:
        Asteroid(const glm::vec3& position, GLuint texture, GLint num_elements, GLuint dest_texture);

        // Update function for moving the player object around
        void Update(double delta_time) override;
        bool ValidCollision(GameObject* other_game_object, double deltatime);
        bool HandleCollision(GameObject* other_game_object, double deltatime);
    private:

    }; // class Asteroid

} // namespace game
