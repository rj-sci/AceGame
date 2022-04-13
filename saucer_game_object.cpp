#include "saucer_game_object.h"
#include "fire_game_object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

namespace game
{
    //Constructor
    SaucerGameObject::SaucerGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* p, GLuint laserTex, GLuint hurt_tex,float radius)
        : EnemyGameObject(position, texture, num_elements,hurt_tex,1, 3) {
        target_ = p;
        fireball_ = new FireGameObject(position, laserTex, num_elements, this);
    }

    //Update
    void SaucerGameObject::Update(double delta_time, double current_time)
    {
        float x = cos(rotation_ * (3.14159265 / 180)) * 3.0f;
        float y = sin(rotation_ * (3.14159265 / 180)) * 3.0f;

        SetVelocity(glm::vec3(x, y, 0.0f));
        position_ += velocity_ * ((float)delta_time);
        rotation_ += 2.0f;

        fireball_->Update(delta_time, current_time);

        EnemyGameObject::Update(delta_time, current_time);
        
    }

    void SaucerGameObject::Render(Shader& shader, glm::mat4 view_matrix, double current_time)
    {

        // Bind the entity's texture
        glBindTexture(GL_TEXTURE_2D, texture_);

        // Setup the scaling matrix for the shader
        glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

        // Set up the translation matrix for the shader
        glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

        //glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));

        parent_transformation_ = translation_matrix;

        // Setup the transformation matrix for the shader
        glm::mat4 transformation_matrix = translation_matrix * scaling_matrix;

        // Set the transformation matrix in the shader
        shader.SetUniformMat4("transformation_matrix", transformation_matrix);

        // Draw the entity
        glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);

        fireball_->Render(shader, view_matrix, current_time);
        
    }
}
