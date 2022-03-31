#ifndef LASER_GAME_OBJECT_H_
#define LASER_GAME_OBJECT_H_

#include "game_object.h"

namespace game
{
	class LaserGameObject : public GameObject
	{
		public:
			LaserGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* p);
			void Update(double delta_time);
			void Render(Shader& shader);

		private:
			GameObject* target_;
	};
		
		
}

#endif