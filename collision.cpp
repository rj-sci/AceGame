
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "collision.h"
bool game::Collision::FindCollisions(int i, std::vector<GameObject*>* game_objects_, game::GameObject* current_game_object, double deltatime) {
	// Check for collision with other game objects
	int vecsize_ = game_objects_->size();
	//std::cout << vecsize_;
	for (int j = 0; j < vecsize_; j++) {
		GameObject* other_game_object = (*game_objects_)[j];
		//std::cout << current_game_object->GetName();
		if (j != i && current_game_object->ValidCollision(other_game_object, deltatime) == true) {
			double time = glfwGetTime();
			current_game_object->HandleCollision(other_game_object, deltatime);
			other_game_object->HandleCollision(current_game_object, deltatime);
		}
	}
	return 0;
}
bool game::Collision::CircleCircleCollision(game::GameObject* other_game_object, glm::vec3 position, float radius) {
	float distance = glm::length(position - other_game_object->GetPosition());
	float radii = other_game_object->GetRadius() + radius;
	if (distance < radii) {
		return true;
	}
	return false;
}
bool game::Collision::RayCircleCollision(game::GameObject* other_game_object, glm::vec3 initial_position, glm::vec3 velocity, float last_t, float current_t) {
	glm::vec3 pmc(initial_position - other_game_object->GetPosition());
	float a = glm::dot(velocity, velocity);
	float b = glm::dot(2.0f * velocity, pmc);
	// May need to fine-tune the default radius for best effects
	float r = other_game_object->GetRadius();
	float c = glm::dot(pmc, pmc) - r * r;

	// Solve quadratic equation
	float det = b * b - 4.0f * a * c;

	// Check if there are real solutions,
	// if not, there is no intersection with object "i"
	if (det < 0.0f) {
		return false;
	}
	float t1 = (-b + sqrt(det)) / (2 * a);
	float t2 = (-b - sqrt(det)) / (2 * a);

	if ((t1 > last_t) && (t1 < current_t)) {
		return true;
	}
	if ((t2 > last_t) && (t2 < current_t)) {
		return true;
	}
	return false;
}
