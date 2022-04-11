#pragma once
#include "game_object.h"

#define SHIELD_SCALE 4
namespace game {

    // Class that abstracts a shield around the player
    // Inherits from GameObject
    class Shield : public GameObject {

    public:
        Shield(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* parent);

        void Update(double delta_time, double current_time) override;

        //inherited virtual member functions
        bool ValidCollision(GameObject* other_game_object, double deltatime);
        bool HandleCollision(GameObject* other_game_object, double deltatime);

    private:
        GameObject* parent_;

        float orbit_angle_;

    }; // class Shield

} // namespace game

