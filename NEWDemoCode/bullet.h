#pragma once
#include <string>
#include <string>
#include "game_object.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include "game_object.h"
#include <GLFW/glfw3.h>

#define BULLET_SPEED 2;
#define BULLET_EXPIRY 2
namespace game {
	class Bullet : public GameObject {
		public:
			Bullet(const glm::vec3& position, GLuint texture, GLint num_elements, double damage, float rotation, float time);

			void Update(double delta_time) override;
			void Destroy(void);
			void Render(Shader& shader);
			//getters
			inline float getTime(void) { return time_; }
			//other
			bool ValidCollision(GameObject* other_game_object);
		private:
			double damage_;
			float time_;
			//variable that represents the ray of the bullet
			glm::vec3 ray_;
			int past_t;
	};
}