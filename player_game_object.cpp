#include "player_game_object.h"
#include "collision.h"

namespace game {

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(const glm::vec3 &position, GLuint texture, GLint num_elements)
	: GameObject(position, texture, num_elements, true, 0.5) {
	
	power_up_ = None;
	name_ = player;
	}

// Update function for moving the player object around
void PlayerGameObject::Update(double delta_time) {
	// Special player updates go here

	glm::vec3 v = GetVelocity();

	if (v.x > 0.0)
	{
		v.x = v.x - 0.0065;

		if (v.x < 0.0)
		{
			v.x = 0;
		}
	}

	if (v.y > 0.0)
	{
		v.y = v.y - 0.0065;

		if (v.y < 0.0)
		{
			v.y = 0;
		}
	}

	if (v.x < 0.0)
	{
		v.x = v.x + 0.0065;

		if (v.x > 0.0)
		{
			v.x = 0;
		}
	}

	if (v.y < 0.0)
	{
		v.y = v.y + 0.0065;

		if (v.y > 0.0)
		{
			v.y = 0;
		}
	}

	SetVelocity(glm::vec3(v.x, v.y, 0.0f));
	// Call the parent's update method to move the object in standard way, if desired
	GameObject::Update(delta_time);
}

void PlayerGameObject::Render(Shader& shader)
{

	GameObject::Render(shader);
}
bool PlayerGameObject::ValidCollision(GameObject* other_game_object, double deltatime) {
	switch (other_game_object->GetName()) {
		case enemy:
			return Collision::CicleCircleCollision(other_game_object, position_, radius_);
		case powerup:
			return Collision::CicleCircleCollision(other_game_object, position_, radius_);
		}
}
bool PlayerGameObject::HandleCollision(GameObject* other_game_object, double deltatime) 
{
	switch (other_game_object->GetName()) {
		case enemy:
			dead_ = true;

		case powerup:
			//downcast, prett ew-ish but couldn't think of anything else
			PowerUp* pwrup = (PowerUp*)other_game_object;
			power_up_ = pwrup->GetType();
	}
	return true;
}

} // namespace game
