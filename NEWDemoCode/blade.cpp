
#include "blade.h"

namespace game {
    Blade::Blade(const glm::vec3& position, GLuint texture, GLint num_elements)
    : GameObject(position, texture, num_elements, false, false, "blade") {
        rotation_ = 0;
    }

    // Update function for moving the player object around
    void Blade::Update(double delta_time) {
        rotation_ += 1;
    }

    void Blade::Render(Shader& shader, glm::mat4 mat_){
        // Bind the entity's texture
        glBindTexture(GL_TEXTURE_2D, texture_);

        //local rotation matrix for blade
        glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
        // Setup the transformation matrix for the shader
        glm::mat4 transformation_matrix = mat_ * rotation_matrix;

        // Set the transformation matrix in the shader
        shader.SetUniformMat4("transformation_matrix", transformation_matrix);

        // Draw the entity
        glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
    }
    void Blade::Destroy() {
        
    }
    bool Blade::ValidCollision(GameObject* other_game_object) {
       return GameObject::ValidCollision(other_game_object);
    }
}