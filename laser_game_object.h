#ifndef LASER_GAME_OBJECT_H_
#define LASER_GAME_OBJECT_H_

#include "game_object.h"
#include "collision.h"

namespace game
{
	class LaserGameObject : public GameObject
	{
		public:
			LaserGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* p);
			void Update(double delta_time, double current_time);
			void Render(Shader& shader, glm::mat4 view_matrix, double current_time);
			bool ValidCollision(GameObject* other_game_object, double deltatime);
			bool HandleCollision(GameObject* other_game_object, double deltatime);
		private:
			GameObject* target_;
			// Time of current frame since the creation of the bullet
			float current_t_;

			// Time of the previous frame
			float last_t_;

			float orbit_angle_;
	};
		
		
}

#endif