#include "alien_game_object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

namespace game {

    //AlienGameObject constructor
    AlienGameObject::AlienGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* p, GLuint bulletTexture, GLuint hurt_tex)
        : EnemyGameObject(position, texture, num_elements, hurt_tex, 1, 3)
    {
        target_ = p;
        last_occurence_ = 0.0;
        state_ = false;
        bullet_texture_ = bulletTexture;
        cool_down_ = -1.0;
    }

    //Checks distance between player and the alien. If it's close enough, the state is set to chase mode
    void AlienGameObject::CheckDistance()
    {
        glm::vec3 playerPosition = target_->GetPosition();

        float tempX = pow((playerPosition.x - position_.x), 2);
        float tempY = pow((playerPosition.y - position_.y), 2);
        float distance = sqrt(tempX + tempY);

        if (distance <= 2.5f)
        {
            SetState(true);
        }
        else
        {
            SetState(false);
        }
    }

    //Update function for the alien
    void AlienGameObject::Update(double delta_time, double current_time)
    {
        time_since_hit_ += delta_time;
        if (texture_ == hurt_texture_ && time_since_hit_ > 0.5) {
            texture_ = default_texture_;
        }
        CheckDistance();
        if (state_ == false)
        {
            position_ += velocity_ * ((float)delta_time);
            last_occurence_ = 0.0;
            
        }
        else
        {

            glm::vec3 playerPosition = target_->GetPosition();
            glm::vec3 tempEnemyPosition = glm::vec3(position_.x * (1 - last_occurence_), position_.y * (1 - last_occurence_), 0.0f);
            glm::vec3 tempPlayerPosition = glm::vec3(last_occurence_ * playerPosition.x, last_occurence_ * playerPosition.y, 0.0f);
            glm::vec3 updatedPosition = (tempPlayerPosition + tempEnemyPosition);

            SetPosition(updatedPosition);


            last_occurence_ = last_occurence_ + 0.00015;
            cool_down_ = -1.0f;

        }

        if (state_ == false)
        {
            if (cool_down_ == -1.0f || glfwGetTime() - cool_down_ >= 5.0)
            {
                cool_down_ = glfwGetTime();

                Bullet* bullet = new Bullet(GetPosition(), bullet_texture_, num_elements_, enemy, glfwGetTime(), target_, this);
                bullet->SetRotation(GetRotation()); // Orient bullet with direction it is going
                bullet->SetScale(0.15);


                // Add bullet at the end of list
                bullets_.push_back(bullet);

                // Set cooldown period in seconds
                cool_down_ = glfwGetTime();
            }
        }

        //Update and render each bullet

        for (int i = 0; i < bullets_.size(); i++)
        {
            bullets_[i]->Update(delta_time, current_time);
        }

        for (int i = 0; i < bullets_.size(); i++)
        {
            if (bullets_[i]->GetDead())
            {
                bullets_.erase(bullets_.begin() + i);
            }
            
        }

        EnemyGameObject::Update(delta_time, current_time);
    }


    //Render function for alien
    void AlienGameObject::Render(Shader& shader, glm::mat4 view_matrix, double current_time)
    {
        GameObject::Render(shader, view_matrix, current_time);

        for (int i = 0; i < bullets_.size(); i++)
        {
            bullets_[i]->Render(shader, view_matrix, current_time);
        }
    }
}


