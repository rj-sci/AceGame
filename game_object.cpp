#include <glm/gtc/matrix_transform.hpp>

#include "game_object.h"

namespace game {

GameObject::GameObject(const glm::vec3 &position, GLuint texture, GLint num_elements, bool collidable, double radius, Name type) 
{

    // Initialize all attributes
    position_ = position;
    scale_ = 1.0;
    velocity_ = glm::vec3(0.0f, 0.0f, 0.0f); // Starts out stationary
    num_elements_ = num_elements;
    texture_ = texture;
    collidable_ = collidable;
    radius = radius_; 
    rotation_ = 0.0f;
    name_ = type;
}


void GameObject::Update(double delta_time) {

    // Update object position with Euler integration
    position_ += velocity_ * ((float) delta_time);
}


void GameObject::Render(Shader &shader) {

    // Bind the entity's texture
    glBindTexture(GL_TEXTURE_2D, texture_);

    // Setup the scaling matrix for the shader
    glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

    // Set up the translation matrix for the shader
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));

    // Setup the transformation matrix for the shader
    glm::mat4 transformation_matrix =  translation_matrix * rotation_matrix  * scaling_matrix;

    // Set the transformation matrix in the shader
    shader.SetUniformMat4("transformation_matrix", transformation_matrix);

    // Draw the entity
    glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
}
bool GameObject::CCCollision(GameObject* other_game_object) {
    float distance = glm::length(position_ - other_game_object->GetPosition());
    float radii = other_game_object->GetRadius() + radius_;
    if (distance < radii) {
        std::cout << "collision found";
        return true;
    }return false;
}

} // namespace game
