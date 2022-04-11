#pragma once
#include <vector>
#include "game_object.h"

#define BULLET_SPEED 3
namespace game {

    // Class that abstracts a bullet fired from a game object
    // Inherits from GameObject
    class Bullet : public GameObject {

    public:
        static float current_t;
        Bullet(const glm::vec3& position, GLuint texture, GLint num_elements,Name firer, double spawnTime, GameObject* p = NULL, GameObject* c = NULL);

        // Update function for moving the player object around
        void Update(double delta_time, double current_time) override;

        inline Name GetFirer() { return firer_; }

        bool ValidCollision(GameObject* other_game_object, double deltatime);
        bool HandleCollision(GameObject* other_game_object, double deltatime);

        void CheckLife(double current_time) override;

    private:
        // Initial position of the ray
        // This is different from the current position stored in position_
        glm::vec3 initial_pos_;

        // Time of current frame since the creation of the bullet
        float current_t_;

        // Time of the previous frame
        float last_t_;
        Name firer_;

        float spawn_t_;

        GameObject* target_;
        GameObject* creator_;

        double last_occurence_;

    }; // class Bullet

} // namespace game