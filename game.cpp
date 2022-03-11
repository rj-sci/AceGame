#include <stdexcept>
#include <string>
#include <glm/gtc/matrix_transform.hpp> 
#include <SOIL/SOIL.h>

#include <path_config.h>

#include "shader.h"
#include "player_game_object.h"
#include "game.h"
#include "collision.h"
namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Globals that define the OpenGL window and viewport
const char *window_title_g = "Game Demo";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const glm::vec3 viewport_background_color_g(0.0, 0.0, 1.0);

// Directory with game resources such as textures
const std::string resources_directory_g = RESOURCES_DIRECTORY;


Game::Game(void)
{
    // Don't do work in the constructor, leave it for the Init() function
}


void Game::Init(void)
{

    // Initialize the window management library (GLFW)
    if (!glfwInit()) {
        throw(std::runtime_error(std::string("Could not initialize the GLFW library")));
    }

    // Set window to not resizable
    // Required or else the calculation to get cursor pos to screenspace will be incorrect
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 

    // Create a window and its OpenGL context
    window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g, NULL, NULL);
    if (!window_) {
        glfwTerminate();
        throw(std::runtime_error(std::string("Could not create window")));
    }

    // Make the window's OpenGL context the current one
    glfwMakeContextCurrent(window_);

    // Initialize the GLEW library to access OpenGL extensions
    // Need to do it after initializing an OpenGL context
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        throw(std::runtime_error(std::string("Could not initialize the GLEW library: ") + std::string((const char *)glewGetErrorString(err))));
    }

    // Set event callbacks
    glfwSetFramebufferSizeCallback(window_, ResizeCallback);

    // Set up square geometry
    size_ = CreateSprite();

    // Initialize shader
    shader_.Init((resources_directory_g+std::string("/vertex_shader.glsl")).c_str(), (resources_directory_g+std::string("/fragment_shader.glsl")).c_str());
    shader_.Enable();

    // Set up z-buffer for rendering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enable Alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    max_y_ = 10.0;
    min_y_ = -10.0;

    max_x_ = 10.0;
    min_x_ = -10.0;
}


Game::~Game()
{

    glfwDestroyWindow(window_);
    glfwTerminate();
}


void Game::Setup(void)
{

    // Load textures
    SetAllTextures();

    // Setup the player object (position, texture, vertex count)
    // Note that, in this specific implementation, the player object should always be the first object in the game object vector 
    game_objects_.push_back(new PlayerGameObject(glm::vec3(0.0f, 0.0f, 0.0f), tex_[0], size_));

    // Setup other objects
    game_objects_.push_back(new GameObject(glm::vec3(-1.0f, 1.0f, 0.0f), tex_[1], size_, true, 0.5f));
    game_objects_.push_back(new GameObject(glm::vec3(1.0f, -0.5f, 0.0f), tex_[2], size_, true, 0.5f));

    // Setup background

    for (int i = -10; i <= 10; i += 10)
    {
        for (int j = -10; j <= 10; j += 10)
        {
            tile_map_.push_back(new GameObject(glm::vec3(i, j, 0.0f), tex_[3], size_, false, 0.5f));
            tile_map_[tile_map_.size() - 1]->SetScale(10.0);
        }
    }
}


void Game::MainLoop(void)
{

    // Loop while the user did not close the window
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window_)){

        // Clear background
        glClearColor(viewport_background_color_g.r,
                     viewport_background_color_g.g,
                     viewport_background_color_g.b, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set view to zoom out, centered by default at 0,0
        float cameraZoom = 0.25f;
        GameObject* player = game_objects_[0];

        glm::vec3 player_position = player->GetPosition();
        glm::vec3 cameraPosition = glm::vec3(player_position.x * 0.25, player_position.y * 0.25, 0.0f);

        glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), -cameraPosition);
        glm::mat4 view_matrix = translation_matrix * glm::scale(glm::mat4(1.0f), glm::vec3(cameraZoom, cameraZoom, cameraZoom));
        shader_.SetUniformMat4("view_matrix", view_matrix);

        // Calculate delta time
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Update the game
        Update(deltaTime);

        // Push buffer drawn in the background onto the display
        glfwSwapBuffers(window_);

        // Update other events like input handling
        glfwPollEvents();
    }
}


void Game::ResizeCallback(GLFWwindow* window, int width, int height)
{

    // Set OpenGL viewport based on framebuffer width and height
    glViewport(0, 0, width, height);
}


// Create the geometry for a sprite (a squared composed of two triangles)
// Return the number of array elements that form the square
int Game::CreateSprite(void)
{
    // The face of the square is defined by four vertices and two triangles

    // Number of attributes for vertices and faces
    // const int vertex_att = 7;  // 7 attributes per vertex: 2D (or 3D) position (2), RGB color (3), 2D texture coordinates (2)
    // const int face_att = 3; // Vertex indices (3)

    GLfloat vertex[]  = {
        // Four vertices of a square
        // Position      Color                Texture coordinates
        -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f, // Top-left
         0.5f,  0.5f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // Top-right
         0.5f, -0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f  // Bottom-left
    };

    // Two triangles referencing the vertices
    GLuint face[] = {
        0, 1, 2, // t1
        2, 3, 0  //t2
    };

    // OpenGL buffers
    GLuint vbo, ebo;

    // Create buffer for vertices
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    // Create buffer for faces (index buffer)
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

    // Return number of elements in array buffer (6 in this case)
    return sizeof(face) / sizeof(GLuint);
}


void Game::SetTexture(GLuint w, const char *fname)
{
    // Bind texture buffer
    glBindTexture(GL_TEXTURE_2D, w);

    // Load texture from a file to the buffer
    int width, height;
    unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    // Texture Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Texture Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Game::SetAllTextures(void)
{
    // Load all textures that we will need
    glGenTextures(NUM_TEXTURES, tex_);
    SetTexture(tex_[0], (resources_directory_g+std::string("/textures/spacecraft.png")).c_str());
    SetTexture(tex_[1], (resources_directory_g+std::string("/textures/asteroid.png")).c_str());
    SetTexture(tex_[2], (resources_directory_g+std::string("/textures/asteroid.png")).c_str());
    SetTexture(tex_[3], (resources_directory_g+std::string("/textures/space.png")).c_str());
    glBindTexture(GL_TEXTURE_2D, tex_[0]);
}


void Game::Controls(void)
{
    // Get player game object
    GameObject *player = game_objects_[0];
    glm::vec3 curpos = player->GetPosition();
    float currot = player->GetRotation();

    // Check for player input and make changes accordingly
    if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
        float angle = player->GetRotation();

        if (angle < 270)
        {
            angle = angle + 90;
        }
        else
        {
            angle = angle - 270;
        }

        float x = cos(angle * (3.14159265 / 180)) * 0.03;
        float y = sin(angle * (3.14159265 / 180)) * 0.03;


        glm::vec3 v = player->GetVelocity();

        glm::vec3 max_v = glm::vec3(1.500, 1.500, 0.0f);

        glm::vec3 newVelocity = glm::vec3(v.x + x, v.y + y, 0.0f);

        if (newVelocity.x > max_v.x)
        {
            newVelocity.x = max_v.x;
        }

        if (newVelocity.y > max_v.y)
        {
            newVelocity.y = max_v.y;
        }

        player->SetVelocity(newVelocity);
    }
    if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
        float angle = player->GetRotation();

        if (angle < 270)
        {
            angle = angle + 90;
        }
        else
        {
            angle = angle - 270;
        }
        float x = cos(angle * (3.14159265 / 180)) * -0.03;
        float y = sin(angle * (3.14159265 / 180)) * -0.03;

        glm::vec3 v = player->GetVelocity();

        glm::vec3 min_v = glm::vec3(-1.500, -1.500, 0.0f);

        glm::vec3 newVelocity = glm::vec3(v.x + x, v.y + y, 0.0f);

        if (newVelocity.x < min_v.x)
        {
            newVelocity.x = min_v.x;
        }

        if (newVelocity.y < min_v.y)
        {
            newVelocity.y = min_v.y;
        }

        player->SetVelocity(newVelocity);
        //player->SetPosition(glm::vec3(curpos.x + x, curpos.y + y, 0.0f));
    }
    if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) 
    {
        player->SetRotation(currot - 1);
    }
    if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) 
    {
        player->SetRotation(currot + 1);
    }
    if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_, true);
    }
}


void Game::Update(double delta_time)
{

    // Handle user input
    Controls();

    GameObject* player = game_objects_[0];

    UpdateTiles(player);

    // Update and render all game objects
    for (int i = 0; i < game_objects_.size(); i++) {
        // Get the current game object
        GameObject* current_game_object = game_objects_[i];

        // Update the current game object
        current_game_object->Update(delta_time);
        if (current_game_object->GetCollidable()) {
            Collision::FindCollisions(&game_objects_, current_game_object);
        }
        // Check for collision with other game objects
        // Render game object
        current_game_object->Render(shader_);
    }

    for (int i = 0; i < tile_map_.size(); i++)
    {
        GameObject* current_tile = tile_map_[i];
        current_tile->Update(delta_time);
        current_tile->Render(shader_);
    }
}

void Game::UpdateTiles(GameObject* player)
{
    glm::vec3 pos = player->GetPosition();


    if (pos.y >= max_y_)
    {
        for (int i = 0; i < tile_map_.size(); i++)
        {
            GameObject* current_tile = tile_map_[i];

            glm::vec3 pos = current_tile->GetPosition();

            current_tile->SetPosition(glm::vec3(pos.x, pos.y + 10.0f, 0.0f));
        }

        max_y_ = max_y_ + 10;
        min_y_ = min_y_ + 10;
    }


    if (pos.y <= min_y_)
    {
        for (int i = 0; i < tile_map_.size(); i++)
        {
            GameObject* current_tile = tile_map_[i];

            glm::vec3 pos = current_tile->GetPosition();

            current_tile->SetPosition(glm::vec3(pos.x, pos.y - 10.0f, 0.0f));
        }

        max_y_ = max_y_ - 10;
        min_y_ = min_y_ - 10;
    }

    if (pos.x >= max_x_)
    {
        for (int i = 0; i < tile_map_.size(); i++)
        {
            GameObject* current_tile = tile_map_[i];

            glm::vec3 pos = current_tile->GetPosition();

            current_tile->SetPosition(glm::vec3(pos.x + 10.0f, pos.y, 0.0f));
        }

        max_x_ = max_x_ + 10;
        min_x_ = min_x_ + 10;
    }

    if (pos.x <= min_x_)
    {
        for (int i = 0; i < tile_map_.size(); i++)
        {
            GameObject* current_tile = tile_map_[i];

            glm::vec3 pos = current_tile->GetPosition();

            current_tile->SetPosition(glm::vec3(pos.x - 10.0f, pos.y, 0.0f));
        }

        max_x_ = max_x_ - 10;
        min_x_ = min_x_ - 10;
    }
}
       
} // namespace game
