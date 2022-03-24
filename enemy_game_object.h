#pragma once
#include <string>
#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class EnemyGameObject : public GameObject {

    public:
        EnemyGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GLuint dest_texture,Name name, int damage);

        // Update function for moving the player object around
    private:
        GLuint dest_texture_;
        bool dead_;
        int damage_;
    }; // class EnemyGameObject

} // namespace game