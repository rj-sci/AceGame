#pragma once

#include "game_object.h"
#include "game.h"
namespace game {
	class Collision {
	public:
		static bool game::Collision::FindCollisions(int i, std::vector<GameObject*>* game_objects_, game::GameObject* current_game_object, double deltatime);
	};
}
