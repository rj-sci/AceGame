#pragma once
#include <string>
#include "game_object.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
namespace game {

    // Inherits from GameObject
    class Blade : public GameObject {

    public:
        Blade (const glm::vec3& position, GLuint texture, GLint num_elements);

        // Update function for moving the player object around
        void Update(double delta_time) override;

        void Render(Shader& shader, glm::mat4 mat_);
        void Destroy(void);
        bool ValidCollision(GameObject* other_game_object);


    private:
        double radi;
        int rotation;
    }; // class EnemyGameObject

} // namespace game
