#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include "shader.h"
#include <string>

namespace game {

    /*
        GameObject is responsible for handling the rendering and updating of objects in the game world
        The update method is virtual, so you can inherit from GameObject and override the update functionality (see PlayerGameObject for reference)
    */
    class GameObject {

        public:
            // Constructor
            GameObject(const glm::vec3 &position, GLuint texture, GLint num_elements, bool collidable, float radius, std::string name);

            // Update the GameObject's state. Can be overriden for children
            virtual void Update(double delta_time);

            // Renders the GameObject using a shader
           virtual void Render(Shader &shader);

            // Getters
            inline glm::vec3& GetPosition(void) { return position_; }
            inline float GetScale(void) { return scale_; }
            inline glm::vec3& GetVelocity(void) { return velocity_; }
            inline float GetAcceleration(void) { return acceleration_; }
            inline float GetMultiplier(void) { return multiplier_; }
            inline float GetRotation() { return rotation_; }
            inline bool GetCollidable() { return collidable_; }
            inline float GetRadius() { return radius_; }
            inline std::string GetName() { return name_;  }
            inline bool GetDead() { return dead_; }
            inline float GetDeathTime() { return death_time_; }
            inline int GetTimer() { return timer; }
            // Setters
            inline void SetPosition(const glm::vec3& position) { position_ = position; }
            inline void SetAcceleration(float acceleration) { acceleration_ = acceleration; }
            inline void SetScale(float scale) { scale_ = scale; }
            inline void SetRotation(float rotation) { rotation_ = rotation; }
            inline void SetVelocity(const glm::vec3& velocity) { velocity_ = velocity; }
            inline void SetMultiplier(float multiplier) { multiplier_ = multiplier; }
            inline void setRadius(float radius) { radius_ = radius; }
            inline void SetTexture(GLint texture) { texture_ = texture; }
            inline void SetDeathTime(float death_time) { death_time_ = death_time; }
            //other
            virtual void Destroy(void);
            virtual bool ValidCollision(GameObject* other_game_object);
        protected:
            // Object's Transform Variables
            // TODO: Add more transformation variables
            glm::vec3 position_;
            float scale_; 
            glm::vec3 velocity_;
            float rotation_;
            // Object's details
            GLint num_elements_;
            float acceleration_;
           // glm::vec3 accel_;
            float multiplier_;
            bool collidable_;
            float radius_;
            // Object's texture reference
            GLuint texture_;
            std::string name_;
            bool dead_;
            float death_time_;
            int timer;
    }; // class GameObject

} // namespace game

#endif // GAME_OBJECT_H_
