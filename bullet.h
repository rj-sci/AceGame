#pragma once
#include <vector>
#include "game_object.h"

namespace game {

    // Class that abstracts a bullet fired from a game object
    // Inherits from GameObject
    class Bullet : public GameObject {

    public:
        Bullet(const glm::vec3& position, GLuint texture, GLint num_elements,Name firer);

        // Update function for moving the player object around
        void Update(double delta_time) override;

        bool ValidCollision(GameObject* other_game_object, double deltatime);
        bool HandleCollision(GameObject* other_game_object, double deltatime);

    private:
        // Initial position of the ray
        // This is different from the current position stored in position_
        glm::vec3 initial_pos_;

        // Time of current frame since the creation of the bullet
        float current_t_;

        // Time of the previous frame
        float last_t_;
        Name firer_;

    }; // class Bullet

} // namespace game