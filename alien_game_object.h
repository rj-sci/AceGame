#pragma once
#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include "game_object.h"
#include "shader.h"
#include "enemy_game_object.h"
#include "powerup.h"
#include "defs.h"
#include "collision.h"
#include "bullet.h"

namespace game {

    /*
        GameObject is responsible for handling the rendering and updating of objects in the game world
        The update method is virtual, so you can inherit from GameObject and override the update functionality (see PlayerGameObject for reference)
    */
    class AlienGameObject : public GameObject {
    public:

        AlienGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* p, bool collidable, float radius, Name name, GLuint bulletTexture);
        inline void SetState(bool s) { state_ = s; }
        inline bool GetState() { return state_; }

        inline std::vector<GameObject*> GetBullets() { return bullets_; }

        void Update(double delta_time);

        virtual void Render(Shader& shader, glm::mat4 view_matrix, double current_time);

        bool ValidCollision(GameObject* other_game_object, double deltatime);
        bool HandleCollision(GameObject* other_game_object, double deltatime);
        //void Render(Shader& shader);
        void CheckDistance();

    private:

        //If state is true - moving
        //If false - patrolling
        bool state_;

        double last_occurence_;
        double cool_down_;

        GLuint bullet_texture_;


        GameObject* target_;

        std::vector<GameObject*> bullets_;

    };

} // namespace game

 // GAME_OBJECT_H_