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

namespace game {

    /*
        GameObject is responsible for handling the rendering and updating of objects in the game world
        The update method is virtual, so you can inherit from GameObject and override the update functionality (see PlayerGameObject for reference)
    */
    class AsteroidGameObject : public EnemyGameObject {
    public:

        AsteroidGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, glm::vec3 dir, GLuint hurt_tex);

        void Update(double delta_time, double current_time);
        //void Render(Shader& shader);
        void TakeDamage(int amt, double deltatime);


    private:

        GameObject* target;
        glm::vec3 dir_;
        int health_;
        float life_timer_;
    };

} // namespace game

 // GAME_OBJECT_H_