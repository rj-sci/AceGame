#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_
class GameObject; 
#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"
#include "defs.h"

namespace game {

    /*
        GameObject is responsible for handling the rendering and updating of objects in the game world
        GameObject is also a virtual class, to prevent ambiguity when making objects
        The update method is virtual, so you can inherit from GameObject and override the update functionality (see PlayerGameObject for reference)
        
    */
    class GameObject {

        public:
            // Constructor
            GameObject(const glm::vec3 &position, GLuint texture, GLint num_elements, bool collidable_, float radius);

            // Update the GameObject's state. Can be overriden for children
            virtual void Update(double delta_time);

            // Renders the GameObject using a shader
            virtual void Render(Shader &shader, glm::mat4 view_matrix, double current_time);

            inline virtual void CheckLife(double delta_time) {  }
            // Getters
            inline glm::vec3& GetPosition(void) { return position_; }
            inline float GetScale(void) { return scale_; }
            inline glm::vec3& GetVelocity(void) { return velocity_; }
            inline bool GetCollidable(void) { return collidable_; }
            inline float GetRadius(void) { return radius_; }
            inline float GetRotation(void) { return rotation_; }
            inline Name GetName(void) { return name_; }
            inline bool GetDead(void) { return dead_; }
            inline glm::mat4 GetParentTransformation(void) { return parent_transformation_; }

            // Setters
            inline void SetPosition(const glm::vec3& position) { position_ = position; }
            inline void SetScale(float scale) { scale_ = scale; }
            inline void SetRotation(float rotation) { rotation_ = rotation; }
            inline void SetTexture(GLuint tex) { texture_ = tex; }
            inline void SetVelocity(const glm::vec3& velocity) { velocity_ = velocity; }
            inline void SetRadius(float radius) { radius_ = radius; }
            inline void SetDead(void) { dead_ = true; }
            inline void SetParentTransformation(glm::mat4 p) { parent_transformation_ = p; }
            //Unimplemented virtual functions
                //Collision
                virtual bool ValidCollision(GameObject* other_game_object, double deltatime) = 0;
                virtual bool HandleCollision(GameObject* other_game_object, double deltatime) = 0;
                


        protected:
            // Object's Transform Variables
            // TODO: Add more transformation variables
            glm::vec3 position_;
            float scale_; 
            glm::vec3 velocity_;
            float rotation_;
            float acceleration_;
            float radius_;
            // Object's details
            GLint num_elements_;
            bool collidable_;
            // Object's texture reference
            GLuint texture_;
            //NEW: enum-type class name
            enum Name name_;
            //NEW: bool death checker
            bool dead_;

            glm::vec3 accel_;

            glm::mat4 parent_transformation_;

           

    }; // class GameObject

} // namespace game
#endif // GAME_OBJECT_H_


