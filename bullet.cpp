
#include "bullet.h"
#include "collision.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace game {

	Bullet::Bullet(const glm::vec3& position, GLuint texture, GLint num_elements,Name firer, double spawnTime, GameObject* p, GameObject* c)
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

		creator_ = c;
	}

	void Bullet::Update(double delta_time, double current_time) {

		// Call the parent's update method to move the object in standard way, if desired

		if (firer_ == player)
		{
			double radians = ((2 * 3.1415926536 / 360) * (rotation_ + 90));
			velocity_[0] = cos(radians) * BULLET_SPEED;
			velocity_[1] = sin(radians) * BULLET_SPEED;
			GameObject::Update(delta_time, current_time);

			// Update current and previous time
			last_t_ = current_t_;
			current_t_ += delta_time;

			//last_t_ = current_t;

			

		}

		else if (firer_ == enemy)
		{
			/*glm::vec3 playerPosition = target_->GetPosition();
			glm::vec3 tempEnemyPosition = glm::vec3(position_.x * (1 - last_occurence_), position_.y * (1 - last_occurence_), 0.0f);
			glm::vec3 tempPlayerPosition = glm::vec3(last_occurence_ * playerPosition.x, last_occurence_ * playerPosition.y, 0.0f);
			glm::vec3 updatedPosition = tempPlayerPosition + tempEnemyPosition;*/

			glm::vec3 future = target_->GetPosition() + target_->GetVelocity();
			glm::vec3 direction = future - position_;
			direction = direction / glm::length(direction);
			accel_ = 2.0f*(direction - velocity_);

			velocity_ += accel_ * ((float)delta_time);

			rotation_ = (atan(velocity_.y / velocity_.x) * (180/3.1415926535)) + 90;


			//rotation_ = glm::atan(velocity_.y, velocity_.x) - glm::pi<float>() / 2.0f;
			
			//std::cout << glm::atan(velocity_.y, velocity_.x) << std::endl;

			//std::cout << rotation_ << std::endl;

			//SetPosition(updatedPosition);

			//last_occurence_ = last_occurence_ + 0.00015;

			position_ += velocity_ * ((float)delta_time);
			last_t_ = current_t_;
			current_t_ += delta_time;
			//current_t += delta_time;
		}

		CheckLife(current_time);

	}

	bool Bullet::ValidCollision(GameObject* other_game_object, double deltatime) {
		switch (other_game_object->GetName()) 
		{
		case player:
			return Collision::CircleCircleCollision(other_game_object, position_, 0.0);
		case enemy:
			return Collision::RayCircleCollision(other_game_object, initial_pos_, velocity_, last_t_, current_t_);
		/*default:
			return Collision::RayCircleCollision(other_game_object, initial_pos_, velocity_, last_t_, current_t_);*/
		}
	}
	bool Bullet::HandleCollision(GameObject* other_game_object, double deltatime) 
	{
		switch (this->GetFirer())
		{
			case enemy:
				dead_ = true;
			case player:
				if (other_game_object->GetName() != player)
				{
					dead_ = true;
				}
				
		}
		return true;
	}

	void Bullet::CheckLife(double current_time)
	{
		float limit = 2.0f;
		if (firer_ == enemy)
		{
			limit = 10.0f;
		}
		if (current_time - spawn_t_ >= limit)
		{
			dead_ = true;
		}
	}

} // namespace game