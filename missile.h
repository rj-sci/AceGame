#pragma once
#ifndef ROCKET_H_
#define ROCKET_H_

#include "game_object.h"
#include "collision.h"

namespace game
{
	class Missile : public GameObject
	{
	public:
		Missile(const glm::vec3& position, GLuint texture, GLint num_elements, double spawntime);
		void Update(double delta_time);
		bool ValidCollision(GameObject* other_game_object, double deltatime);
		bool HandleCollision(GameObject* other_game_object, double deltatime);
		void CheckLife(double delta_time);
	private:
		float spawn_t_;
		glm::vec3 initial_pos_;
		// Time of current frame since the creation of the missile
		float current_t_;
		// Time of the previous frame
		float last_t_;
	};


}

#endif