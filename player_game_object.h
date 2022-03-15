#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class PlayerGameObject : public GameObject {

        public:
            PlayerGameObject(const glm::vec3 &position, GLuint texture, GLint num_elements);

            // Update function for moving the player object around
            void Update(double delta_time) override;
            //inherited virtual functions
            bool ValidCollision(GameObject* other_game_object, double deltatime);
            bool HandleCollision(GameObject* other_game_object, double deltatime);
    }; // class PlayerGameObject

} // namespace game

#endif // PLAYER_GAME_OBJECT_H_
