#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <stdexcept>
#include <string>
#include <glm/gtc/matrix_transform.hpp> 
#include <SOIL/SOIL.h>

#include <path_config.h>

#include "shader.h"
#include "defs.h"
#include "game_object.h"

namespace game {

    // A class for holding the main game objects
    class GameOver : public GameObject {

        public:

            GameOver(const glm::vec3& position, GLuint texture, GLint num_elements, bool collidable_, float radius);
            // Constructor and destructor
            ~GameOver();

            virtual void Update(double delta_time, double current_time);
            virtual void Render(Shader& shader, glm::mat4 view_matrix, double current_time);
            virtual bool ValidCollision(GameObject* other_game_object, double deltatime);
            virtual bool HandleCollision(GameObject* other_game_object, double deltatime);


        private:
            


    }; // class Game

} // namespace game
