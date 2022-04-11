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
#include "player_game_object.h"
#include "tile.h"
#include "bullet.h"
#include "powerup.h"
#include "shield.h"
#include "missile.h"
#include "asteroid_game_object.h"
#include "text_game_object.h"

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
            Shader sprite_shader_;
            //Shader for rendering particles
            Shader particle_shader_;

            Shader text_shader_;

            //Pointers to ui elements to simplify things
            //health
            TextGameObject* health_;
            //shield
            TextGameObject* shield_;
            //missiles
            TextGameObject* missiles_;

            // Size of geometry to be rendered
            int size_;

            // References to textures
#define NUM_TEXTURES 21
            GLuint tex_[NUM_TEXTURES];

            // List of game objects
            std::vector<GameObject*> game_objects_;
            PlayerGameObject* player_;
            std::vector<GameObject*> tile_map_;
            //firing of bullets
            double current_time_;
            double cool_down_;

            bool game_over_;
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
            void Update(double delta_time, glm::mat4, glm::mat4);

            void UpdateTiles();

            void SpawnEnemies(void);

            void EnemyGeneration(void);
            //Check for objects that should be removed from the world
            void Game::GetDeadObjects(GameObject* current_game_object, std::vector<GameObject*>* game_objects_, int i);

            int max_y_;
            int min_y_;

            int max_x_;
            int min_x_;
            //variables used for enemy spawning
            double enemy_cooldown_;
            double last_time_;

            GameObject* camera_target_;
            GameObject* game_over_obj_;

    }; // class Game

} // namespace game
