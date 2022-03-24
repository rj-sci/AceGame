#pragma once
#include "game_object.h"
#include <vector>
namespace game {
	class Collision {
	public:
		static bool game::Collision::FindCollisions(int i, std::vector<GameObject*>* game_objects_, GameObject* current_game_object, double deltatime);
		static bool game::Collision::CicleCircleCollision(GameObject* other_game_object, glm::vec3 position, float radius);
		//check for collision when current object is entity and other is some  non-projectle 
		static bool game::Collision::RayCircleCollision(GameObject* other_game_object, glm::vec3 initial_position, glm::vec3 velocity, float last_t, float current_t);
		//check for collision when current object is non-projectle and other is some entity
		static bool game::Collision::CircleRayCollision(GameObject* other_game_object);
	};
}
