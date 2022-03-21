#pragma once
#include "game_object.h"

namespace game {

    // Class that abstracts a shield around the player
    // Inherits from GameObject
    class Shield : public GameObject {

    public:
        Shield(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* parent);

        void Update(double delta_time) override;

        void Render(Shader& shader);

        //inherited virtual member functions
        bool ValidCollision(GameObject* other_game_object, double deltatime);
        bool HandleCollision(GameObject* other_game_object, double deltatime);

    private:
        GameObject* parent_;

        float orbit_angle_;

    }; // class Shield

} // namespace game

