#include "asteroid_game_object.h"

namespace game {
	AsteroidGameObject::AsteroidGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, glm::vec3 dir)
	:	GameObject(position, texture, num_elements, true, 0.5){
		double offset = (3 - (- 2) * ((double)rand() / (double)RAND_MAX) + (- 2));
		double x = (dir.x - position_.x + offset) * 0.3;
		double y = (dir.y - position_.y + offset) * 0.3;
		velocity_ = glm::vec3(x, y , 0);
		scale_ = 3;
		
	}

	void AsteroidGameObject::Update(double delta_time, double current_time) {
		rotation_ += 0.4;
		GameObject::Update(delta_time, current_time);
	}

	bool AsteroidGameObject::ValidCollision(GameObject* other_game_object, double deltatime) {
		switch (other_game_object->GetName()) {
		case player:
			return Collision::CircleCircleCollision(other_game_object, position_, radius_);
		default:
			return false;
		}
	}
	bool AsteroidGameObject::HandleCollision(GameObject* other_game_object, double deltatime) {
		switch (other_game_object->GetName()) {
		case player:
			dead_ = true;
		}
		return true;
	}
}