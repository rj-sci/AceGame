#pragma once
#include <string>
#include "game_object.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "player_game_object.h"

namespace game {
	class PowerUp : public GameObject {
	public:
		PowerUp(const glm::vec3& position, GLuint texture, GLint num_elements, PUpType type);

		void Update(double delta_time) override;
		//getters
		inline PUpType GetType() { return type_; }
		//other
		bool ValidCollision(GameObject* other_game_object, double deltatime);
		bool HandleCollision(GameObject* other_game_object, double deltatime);
	private:
		PUpType type_;
	};
}