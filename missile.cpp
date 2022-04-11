#pragma once
#include "missile.h"
#include "collision.h"
#include <iostream>

namespace game {

	Missile::Missile(const glm::vec3& position, GLuint texture, GLint num_elements, double spawntime, GLuint explo)
		: GameObject(position, texture, num_elements, true, 0.1) {
		initial_pos_ = position;
		current_t_ = 0.0;
		last_t_ = 0.0;
		name_ = missile;
		dead_ = false;
		spawn_t_ = spawntime;
		explosion_ = explo;
		exploded_ = false;
	}

	void Missile::Update(double delta_time, double current_time) {

		// Call the parent's update method to move the object in standard way, if desired
		if (!exploded_) {
			double radians = ((2 * 3.1415926536 / 360) * (rotation_ + 90));
			velocity_[0] = cos(radians) * MISSILE_SPEED * current_t_;
			velocity_[1] = sin(radians) * MISSILE_SPEED * current_t_;
			GameObject::Update(delta_time, current_time);

			// Update current and previous time
			last_t_ = current_t_;
			current_t_ += delta_time;
		}

	}
	bool Missile::ValidCollision(GameObject* other_game_object, double deltatime) {
		switch (other_game_object->GetName()) {
		case enemy:
			//return Collision::RayCircleCollision(other_game_object, initial_pos_, velocity_, last_t_, current_t_);
			return Collision::CircleCircleCollision(other_game_object, position_, radius_);
			break;
		}
	}
	bool Missile::HandleCollision(GameObject* other_game_object, double deltatime) {
		collidable_ = false;
		texture_ = explosion_;
		exploded_ = true;
		return true;
	}

	void Missile::CheckLife(double delta_time)
	{
		if (delta_time - spawn_t_ >= 3.5f)
		{
			dead_ = true;
		}
	}

} // namespace game