#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "game_object.h"
#include "blade.h"
#include "bullet.h"

#define MAX_BULLETS 3


namespace game {

    // Inherits from GameObject
    class PlayerGameObject : public GameObject {

        public:
            PlayerGameObject(const glm::vec3 &position, GLuint texture, GLint num_elements, GLuint dest_texture);

            // Update function for moving the player object around
            void Update(double delta_time) override;

            void Render(Shader& shader) override;
            void Shoot();
            void Destroy();
            //getters
            inline double GetShotTime() { return lastShot_; }
            //setters
            inline void SetShotTime(double lastShot) { lastShot_ = lastShot; }
            //other
            bool ValidCollision(GameObject* other_game_object);
        private:
            Blade *blade_;
            double lastShot_;
            GLuint dest_texture_;
    }; // class PlayerGameObject

} // namespace game

#endif // PLAYER_GAME_OBJECT_H_
