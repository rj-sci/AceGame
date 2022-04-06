#include "bullet.h"
#include "collision.h"
#include <iostream>

namespace game {

	Bullet::Bullet(const glm::vec3& position, GLuint texture, GLint num_elements,Name firer, double spawnTime, GameObject* p)
		: GameObject(position, texture, num_elements, true, 0.5) {

		initial_pos_ = position;
		current_t_ = 0.0;
		last_t_ = 0.0;
		firer_ = firer;
		name_ = bullet;
		dead_ = false;
		spawn_t_ = spawnTime;
		target_ = p;
		last_occurence_ = 0.0;
	}

	void Bullet::Update(double delta_time) {

		// Call the parent's update method to move the object in standard way, if desired

		if (firer_ == player)
		{
			double radians = ((2 * 3.1415926536 / 360) * (rotation_ + 90));
			velocity_[0] = cos(radians) * BULLET_SPEED;
			velocity_[1] = sin(radians) * BULLET_SPEED;
			GameObject::Update(delta_time);

			// Update current and previous time
			last_t_ = current_t_;
			current_t_ += delta_time;
		}

		else if (firer_ == enemy)
		{
			glm::vec3 playerPosition = target_->GetPosition();
			glm::vec3 tempEnemyPosition = glm::vec3(position_.x * (1 - last_occurence_), position_.y * (1 - last_occurence_), 0.0f);
			glm::vec3 tempPlayerPosition = glm::vec3(last_occurence_ * playerPosition.x, last_occurence_ * playerPosition.y, 0.0f);
			glm::vec3 updatedPosition = tempPlayerPosition + tempEnemyPosition;

			SetPosition(updatedPosition);

			last_occurence_ = last_occurence_ + 0.00015;
		}

		
		

	}
	bool Bullet::ValidCollision(GameObject* other_game_object, double deltatime) {
		switch (other_game_object->GetName()) {
		default:
			return Collision::RayCircleCollision(other_game_object, initial_pos_, velocity_, last_t_, current_t_);
		}
	}
	bool Bullet::HandleCollision(GameObject* other_game_object, double deltatime) {
		return true;
	}

	void Bullet::CheckLife(double delta_time)
	{
		if (delta_time - spawn_t_ >= 2.0f)
		{
			dead_ = true;
		}
	}

} // namespace game