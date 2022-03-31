#pragma once
#include "game_object.h"
#include "powerup.h"

namespace game {

    // Inherits from GameObject
    class PlayerGameObject : public GameObject {

        public:
            PlayerGameObject(const glm::vec3 &position, GLuint texture, GLint num_elements);

            // Update function for moving the player object around
            void Update(double delta_time) override;
            void Render(Shader& shader) override;
            //inherited virtual functions
            bool ValidCollision(GameObject* other_game_object, double deltatime);
            bool HandleCollision(GameObject* other_game_object, double deltatime);
            //getters
            inline PUpType GetPowerUp(void) { return power_up_; }
            //setters
            inline void SetPowerUp(PUpType type) { power_up_ = type; }
        private:
            PUpType power_up_;
    }; // class PlayerGameObject

} // namespace game