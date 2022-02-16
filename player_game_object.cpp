#include "player_game_object.h"

namespace game {

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(const glm::vec3 &position, GLuint texture, GLint num_elements)
	: GameObject(position, texture, num_elements, true, 0.5f) {}

// Update function for moving the player object around
void PlayerGameObject::Update(double delta_time) {
	// Special player updates go here

	// Call the parent's update method to move the object in standard way, if desired
	GameObject::Update(delta_time);
}

} // namespace game
