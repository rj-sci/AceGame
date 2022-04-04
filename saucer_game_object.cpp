#include "saucer_game_object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

namespace game
{
    SaucerGameObject::SaucerGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* p, bool collidable, float radius, Name name)
        : GameObject(position, texture, num_elements, collidable, radius) {
        target_ = p;
        name_ = name;
    }


    void SaucerGameObject::Update(double delta_time)
    {
        float x = cos(rotation_ * (3.14159265 / 180)) * 3.0f;
        float y = sin(rotation_ * (3.14159265 / 180)) * 3.0f;

        SetVelocity(glm::vec3(x, y, 0.0f));
        position_ += velocity_ * ((float)delta_time);
        rotation_ += 2.0f;
        /*if (GetCrash())
        {
            return;
        }
        CheckDistance();

        if (state_ == false)
        {
            float x = cos(angle_ * (3.14159265 / 180)) * 3.0f;
            float y = sin(angle_ * (3.14159265 / 180)) * 3.0f;

            SetVelocity(glm::vec3(x, y, 0.0f));
            position_ += velocity_ * ((float)delta_time);
            angle_ += 2.0f;
            last_occurence_ = 0.0;
        }
        else
        {


            glm::vec3 playerPosition = target_->GetPosition();
            glm::vec3 tempEnemyPosition = glm::vec3(position_.x * (1 - last_occurence_), position_.y * (1 - last_occurence_), 0.0f);
            glm::vec3 tempPlayerPosition = glm::vec3(last_occurence_ * playerPosition.x, last_occurence_ * playerPosition.y, 0.0f);
            glm::vec3 updatedPosition = tempPlayerPosition + tempEnemyPosition;

            SetPosition(updatedPosition);

            last_occurence_ = last_occurence_ + 0.00015;

        }*/

    }

    bool SaucerGameObject::ValidCollision(GameObject* other_game_object, double deltatime) 
    {
        switch (other_game_object->GetName()) {
        case player:
            return Collision::CircleCircleCollision(other_game_object, position_, radius_);
        /*case bullet:
            return Collision::CicleCircleCollision(other_game_object, position_, radius_);*/
        }
    }
    bool SaucerGameObject::HandleCollision(GameObject* other_game_object, double deltatime) 
    { 
        switch (other_game_object->GetName()) {
        case player:
            dead_ = true;
            break;
            
        case bullet:
            dead_ = true;
            break;
        }

        return true;
    }

    void SaucerGameObject::Render(Shader& shader, double current_time)
    {

        // Bind the entity's texture
        glBindTexture(GL_TEXTURE_2D, texture_);

        // Setup the scaling matrix for the shader
        glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

        // Set up the translation matrix for the shader
        glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

        //glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));

        // Setup the transformation matrix for the shader
        glm::mat4 transformation_matrix = translation_matrix * scaling_matrix;

        // Set the transformation matrix in the shader
        shader.SetUniformMat4("transformation_matrix", transformation_matrix);

        // Draw the entity
        glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
        
    }
}
