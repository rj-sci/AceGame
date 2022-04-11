#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class ParticleSystem : public GameObject {

    public:
        ParticleSystem(const glm::vec3& position, GLuint texture, int num_elements, GameObject* parent);

        void Update(double delta_time) override;

        void Render(Shader& shader, glm::mat4 view_matrix, double current_time);
        virtual bool ValidCollision(GameObject* other_game_object, double deltatime);
        virtual bool HandleCollision(GameObject* other_game_object, double deltatime);

    private:
        GameObject* parent_;

    }; // class ParticleSystem

} // namespace game

#endif // PARTICLE_SYSTEM_H_
