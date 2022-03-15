#pragma once
#include <string>
#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class EnemyGameObject : public GameObject {

    public:
        EnemyGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GLuint dest_texture, Name type, int damage);

        // Update function for moving the player object around
        void Update(double delta_time) override;
        void Destroy(void);
    private:
        GLuint dest_texture_;
        bool dead_;
        int damage_;
    }; // class EnemyGameObject

} // namespace game