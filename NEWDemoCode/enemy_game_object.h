#ifndef ENEMY_GAME_OBJECT_H_
#define ENEMY_GAME_OBJECT_H_
#include <string>
#include "game_object.h"


#define MIN_VELOCITY 1
#define MAX_VELOCITY 10

namespace game {

    // Inherits from GameObject
    class EnemyGameObject : public GameObject {

    public:
        EnemyGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GLuint dest_texture);

        // Update function for moving the player object around
        void Update(double delta_time) override;

        void Render(Shader& shader) override;
        void Destroy(void);
        bool ValidCollision(GameObject* other_game_object);

    private:
        std::string mode[2] = { "patrol", "moving" };
        std::string currentMode;
        bool found;
        GLuint dest_texture_;
        bool dead_;
    }; // class EnemyGameObject

} // namespace game

#endif // ENEMY_GAME_OBJECT_H_
