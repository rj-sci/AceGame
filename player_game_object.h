#pragma once
#include "game_object.h"
#include "powerup.h"

namespace game {

    // Inherits from GameObject
    class PlayerGameObject : public GameObject {

        public:
            PlayerGameObject(const glm::vec3 &position, GLuint* textures, GLint num_elements);

            // Update function for moving the player object around
            void Update(double delta_time) override;
            //inherited virtual functions
            bool ValidCollision(GameObject* other_game_object, double deltatime);
            bool HandleCollision(GameObject* other_game_object, double deltatime);
            //getters
            inline PUpType GetPowerUp(void) { return power_up_; }
            inline int GetNumMissiles(void) { return num_missiles_; }
            //setters
            inline void SetPowerUp(PUpType type) { power_up_ = type; }
            inline void SetNumMissiles(int num) { num_missiles_ = num; }
            //player specific functions
            void TakeDamage(int amt);
        private:
            PUpType power_up_;
            GLuint shielded_tex_;
            GLuint default_tex_;
            int shield_power_;
            int num_missiles_;
            int health_;
    }; // class PlayerGameObject

} // namespace game