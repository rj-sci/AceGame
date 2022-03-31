#pragma once
#include <string>
#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class Tile : public GameObject {

    public:
        Tile(const glm::vec3& position, GLuint texture, GLint num_elements);

        // Update function for moving the player object around
        void Destroy(void);
        virtual bool ValidCollision(GameObject* other_game_object, double deltatime);
        virtual bool HandleCollision(GameObject* other_game_object, double deltatime);
    }; // class Tile

} // namespace game