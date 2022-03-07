#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "game_object.h"

namespace game {

    GameObject::GameObject(const glm::vec3 &position, GLuint texture, GLint num_elements, bool collidable, float radius, std::string name) {

    // Initialize all attributes
    position_ = position;
    scale_ = 1.0;
    velocity_ = glm::vec3(0.0f, 0.0f, 0.0f); // Starts out stationary
    num_elements_ = num_elements;
    texture_ = texture;
    acceleration_ = 0; // Starts out with no acceleration
    collidable_ = collidable;
    radius_ = radius;
    name_ = name;
    dead_ = false;
    death_time_ = 0;
    timer = 2;
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

    //rotation matrix

    // Setup the transformation matrix for the shader
    glm::mat4 transformation_matrix = scaling_matrix  *  translation_matrix;

    // Set the transformation matrix in the shader
    shader.SetUniformMat4("transformation_matrix", transformation_matrix);

    // Draw the entity
    glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
}
void GameObject::Destroy() {
    dead_ = true;
}
bool GameObject::ValidCollision(GameObject* other_game_object) {
    if (collidable_ && other_game_object->GetCollidable()) {
        return true;
    }
    return false;
}

} // namespace game
