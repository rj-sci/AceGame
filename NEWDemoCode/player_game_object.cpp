#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "player_game_object.h"
#define MIN_VELOCITY 1
#define MAX_VELOCITY 10

namespace game {

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(const glm::vec3 &position, GLuint texture, GLint num_elements,GLuint dest_texture)
	: GameObject(position, texture, num_elements, true, 0.5, "player") {
     rotation_ = 0;
     velocity_ = glm::vec3(0.0f, 1.0f, 0.0f); // Starts out stationary
     dest_texture_ = dest_texture;
     lastShot_ = 0;
    }

// Update function for moving the player object around
void PlayerGameObject::Update(double delta_time) {
    
	//Special player updates go here
    //Update IF not yet dead
    if (dead_ == false) {
        //Velocity:
        double radians = ((2 * 3.1415926536 / 360) * (rotation_ + 90));
        velocity_[0] = cos(radians) * abs(acceleration_);
        velocity_[1] = sin(radians) * abs(acceleration_);
        //Parent Call
        GameObject::Update(delta_time);
        //Hierarchical Updates
        
    }

}
void PlayerGameObject::Render(Shader& shader) {
    // Bind the entity's texture
    glBindTexture(GL_TEXTURE_2D, texture_);

    // Setup the scaling matrix for the shader
    glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

    // Set up the translation matrix for the shader
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

    //rotation matrix
    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));

    // Setup the transformation matrix for the shader
    glm::mat4 transformation_matrix =  translation_matrix * rotation_matrix * scaling_matrix;
    
    // Set the transformation matrix in the shader
    shader.SetUniformMat4("transformation_matrix", transformation_matrix);

    // Draw the entity
    glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
    //draw the blade
}

void PlayerGameObject::Destroy() {
    SetTexture(dest_texture_);
    //delete blade_;
    GameObject::Destroy();
}
bool PlayerGameObject::ValidCollision(GameObject* other_game_object) {
    if (other_game_object->GetName() == "enemy") {
        float distance = glm::length(position_ - other_game_object->GetPosition());
        float radii = other_game_object->GetRadius() + radius_;
        if (distance < radii) {
            return true;
        }
    }return false;
}

} // namespace game
