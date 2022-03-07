#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <cstdlib>
#include "player_game_object.h"
#include "enemy_game_object.h"

namespace game {

    /*
        PlayerGameObject inherits from GameObject
        It overrides GameObject's update method, so that you can check for input to change the velocity of the enemy
    */

    EnemyGameObject::EnemyGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GLuint dest_texture)
        : GameObject(position, texture, num_elements, true, 0.25, "enemy") {
        rotation_ = 0;
        currentMode = mode[0];
        acceleration_ = 0;
        dest_texture_ = dest_texture;
        dead_ = false;
      
        if (currentMode == "moving") {
            int random = rand() % 4 + 1;
            switch (random) {
            case(1):
                rotation_ = 0;
            case(2):
                rotation_ = 90;
            case(3):
                rotation_ = 180;
            case(4):
                rotation_ = 270;
            }
        }
    }

    // Update function for moving the player object around
    void EnemyGameObject::Update(double delta_time) {
        //Special player updates go here
        if (dead_ == false) {
            //patrolling behaviour:
            if (currentMode == "patrol") {
                rotation_ += 0.3;
                velocity_[0] = (cos(rotation_) * radius_);
                velocity_[1] = (sin(rotation_) * radius_);
            }//moving behaviour:
            else if (currentMode == "moving") {
                velocity_[0] = cos(rotation_) + acceleration_;
                velocity_[1] = sin(rotation_) + acceleration_;
            }
            // Call the parent's update method to move the object in standard way, if desired
            GameObject::Update(delta_time);
        }
    }
    void EnemyGameObject::Render(Shader& shader) {
        // Bind the entity's texture
        glBindTexture(GL_TEXTURE_2D, texture_);

        // Setup the scaling matrix for the shader
        glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

        // Set up the translation matrix for the shader
        glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

        //rotation matrix
        glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));

        // Setup the transformation matrix for the shader
        glm::mat4 transformation_matrix = translation_matrix * rotation_matrix * scaling_matrix;

        // Set the transformation matrix in the shader
        shader.SetUniformMat4("transformation_matrix", transformation_matrix);

        // Draw the entity
        glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);

    }
    void EnemyGameObject::Destroy() {
        SetTexture(dest_texture_);
        velocity_[0] = 0;
        velocity_[1] = 0;
        acceleration_ = 0;
        GameObject::Destroy();
    }
    bool EnemyGameObject::ValidCollision(GameObject* other_game_object) {
        if (other_game_object->GetName() == "bullet") {
            float distance = glm::length(position_ - other_game_object->GetPosition());
            double radians = ((2 * 3.1415926536 / 360) * (rotation_ + 90));
            float r2 = pow(distance, 2);
            float a = glm::dot(velocity_, velocity_);
            float b = glm::dot(velocity_ * 2.0f, position_ - other_game_object->GetPosition());
            float c = glm::dot(position_ - other_game_object->GetPosition(), position_ - other_game_object->GetPosition()) - r2;
            float discr = pow(b, 2) - (4 * a * c);
            return true;
        }
        if (other_game_object->GetName() == "player") {
            float distance = glm::length(position_ - other_game_object->GetPosition());
            float radii = other_game_object->GetRadius() + radius_;
            if (distance < radii) {
                return false;
            }
        }
    }
} // namespace game
