#ifndef FIRE_GAME_OBJECT_H_
#define FIRE_GAME_OBJECT_H_

#include "game_object.h"
#include "collision.h"

namespace game
{
	class FireGameObject : public GameObject
	{
		public:
			FireGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* p);
			void Update(double delta_time, double current_time);
			void Render(Shader& shader, glm::mat4 view_matrix, double current_time);
			bool ValidCollision(GameObject* other_game_object, double deltatime);
			bool HandleCollision(GameObject* other_game_object, double deltatime);
		private:
			GameObject* target_;

			glm::vec3 actualPosition_;
			// Time of current frame since the creation of the bullet
			float current_t_;

			// Time of the previous frame
			float last_t_;

			float orbit_angle_;
	};
		
		
}

#endif