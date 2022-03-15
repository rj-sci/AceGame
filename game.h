#ifndef GAME_H_
#define GAME_H_

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
#include "asteroid.h"
#include "player_game_object.h"
#include "collision.h"
#include "tile.h"

namespace game {

    // A class for holding the main game objects
    class Game {

        public:
            // Constructor and destructor
            Game(void);
            ~Game();

            // Call Init() before calling any other method
            // Initialize graphics libraries and main window
            void Init(void); 

            // Set up the game (scene, game objects, etc.)
            void Setup(void);

            // Run the game (keep the game active)
            void MainLoop(void); 

        private:
            // Main window: pointer to the GLFW window structure
            GLFWwindow *window_;

            // Shader for rendering the scene
            Shader shader_;

            // Size of geometry to be rendered
            int size_;

            // References to textures
#define NUM_TEXTURES 6
            GLuint tex_[NUM_TEXTURES];

            // List of game objects
            std::vector<GameObject*> game_objects_;

            std::vector<GameObject*> tile_map_;

            // Callback for when the window is resized
            static void ResizeCallback(GLFWwindow* window, int width, int height);

            // Create a square for drawing textures
            int CreateSprite(void);

            // Set a specific texture
            void SetTexture(GLuint w, const char *fname);

            // Load all textures
            void SetAllTextures();

            // Handle user input
            void Controls(void);

            // Update the game based on user input and simulation
            void Update(double delta_time);

            void UpdateTiles(GameObject* player);

            int max_y_;
            int min_y_;

            int max_x_;
            int min_x_;

    }; // class Game

} // namespace game

#endif // GAME_H_
