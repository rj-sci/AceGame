#pragma once
#ifndef COLLISION_H_
#define COLLISION_H_

#include "game_object.h"
#include "game.h"
namespace game {
	class Collision {
	public:
		bool Collision::FindCollisions(int i, std::vector<GameObject*>* game_objects_, GameObject*);
		bool Collision::ValidCollisionObjs(game::GameObject* current_game_object, game::GameObject* other_game_object);
	};
}
#endif // COLLISION_H