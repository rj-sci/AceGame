#include "alien_game_object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

namespace game {

    AlienGameObject::AlienGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* p, bool collidable, float radius, Name name)
        : GameObject(position, texture, num_elements, collidable, radius)
    {
        name_ = name;
        target_ = p;

        last_occurence_ = 0.0;
        state_ = false;
    }
    void AlienGameObject::CheckDistance()
    {
        glm::vec3 playerPosition = target_->GetPosition();

        float tempX = pow((playerPosition.x - position_.x), 2);
        float tempY = pow((playerPosition.y - position_.y), 2);
        float distance = sqrt(tempX + tempY);

        if (distance <= 3.5f)
        {
            SetState(true);
        }
        else
        {
            SetState(false);
        }
    }

    void AlienGameObject::Update(double delta_time)
    {
        CheckDistance();
        std::cout << state_ << std::endl;
        if (state_ == false)
        {
            /*float x = cos(rotation_ * (3.14159265 / 180)) * 3.0f;
            float y = sin(rotation_ * (3.14159265 / 180)) * 3.0f;*/

            //SetVelocity(glm::vec3(x, y, 0.0f));
            position_ += velocity_ * ((float)delta_time);
            //rotation_ += 2.0f;
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

        }
    }

    bool AlienGameObject::ValidCollision(GameObject* other_game_object, double deltatime)
    {
        switch (other_game_object->GetName()) {
        case player:
            return Collision::CircleCircleCollision(other_game_object, position_, radius_);
            /*case bullet:
                return Collision::CicleCircleCollision(other_game_object, position_, radius_);*/
        }
    }
    bool AlienGameObject::HandleCollision(GameObject* other_game_object, double deltatime)
    {
        switch (other_game_object->GetName()) {
        case player:
            dead_ = true;

        case bullet:
            dead_ = true;
        }

        return true;
    }
}


