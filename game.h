#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "shader.h"
#include "game_object.h"

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
#define NUM_TEXTURES 4
            GLuint tex_[NUM_TEXTURES];

            // List of game objects
            std::vector<GameObject*> game_objects_;

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

    }; // class Game

} // namespace game

#endif // GAME_H_
