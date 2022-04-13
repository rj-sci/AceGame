#include "asteroid_game_object.h"

namespace game {
	//Constructor for the asteroid
	AsteroidGameObject::AsteroidGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, glm::vec3 dir, GLuint hurt_tex)
		: EnemyGameObject(position, texture, num_elements, hurt_tex, 1, 1) {
		double offset = (3 - (-2) * ((double)rand() / (double)RAND_MAX) + (-2));
		double x = (dir.x - position_.x + offset) * 0.3;
		double y = (dir.y - position_.y + offset) * 0.3;
		velocity_ = glm::vec3(x, y, 0);
		scale_ = 3;

		life_timer_ = 0.0f;
		add_name_ = asteroid;
	}

	//Update function for asteroid
	void AsteroidGameObject::Update(double delta_time, double current_time) {
		rotation_ += 0.4;
		time_since_hit_ += delta_time;
		life_timer_ += delta_time;


		if (texture_ == hurt_texture_ && time_since_hit_ > 0.5) {
			texture_ = default_texture_;
		}

		if (life_timer_ >= ASTEROID_LIFE_TIME)
		{
			dead_ = true;
		}
		EnemyGameObject::Update(delta_time, current_time);
		GameObject::Update(delta_time, current_time);
	}

}