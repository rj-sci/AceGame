#include "player_game_object.h"
#include "collision.h"
#include "Bullet.h"

namespace game {

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(const glm::vec3 &position, GLuint* textures, GLint num_elements)
	: GameObject(position, textures[0], num_elements, true, 0.5) {
	power_up_ = None;
	name_ = player;
	health_ = 20;
	shielded_tex_ = textures[1];
	default_tex_ = textures[0];
	hurt_tex_ = textures[2];
	num_missiles_ = 2;
	shield_power_ = 0;
	}

// Update function for moving the player object around
void PlayerGameObject::Update(double delta_time, double current_time) {
	// Special player updates go here
	glm::vec3 v = GetVelocity();
	time_since_hit_ += delta_time;
	if (texture_ == hurt_tex_ && time_since_hit_ > 0.5) {
		texture_ = default_tex_;
	}
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
	GameObject::Update(delta_time, current_time);
}

bool PlayerGameObject::ValidCollision(GameObject* other_game_object, double deltatime) {
	switch (other_game_object->GetName()) {
		case enemy:
			return Collision::CircleCircleCollision(other_game_object, position_, radius_);
		case powerup:
			return Collision::CircleCircleCollision(other_game_object, position_, radius_);
		//Leave laser-player to be handled by Laser class, difficult to call ray-circle here
		}
}
bool PlayerGameObject::HandleCollision(GameObject* other_game_object, double deltatime) 
{
	switch (other_game_object->GetName()) {
		case enemy:
			TakeDamage(2, deltatime);
			break;
		case laser:
			TakeDamage(1, deltatime);
			break;
		case bullet:
		{
			Bullet *b = (Bullet*)other_game_object;
			if (b->GetFirer() == enemy)
			{
				TakeDamage(1, deltatime);
			}
			
			break;
		}
			
		case powerup:
			PowerUp* pwrup = dynamic_cast<PowerUp*>(other_game_object);
			if (pwrup->GetType() == shield_type) {
				texture_ = shielded_tex_;
				power_up_ = shield_type;
				shield_power_ = 3;
			}
			if (pwrup->GetType() == satellite_type) {
				num_missiles_++;
			}
			break;
	}
	return true;
}
void PlayerGameObject::TakeDamage(int amt, double deltatime) {
	if (power_up_ == shield_type) {
		shield_power_--;
		if (shield_power_ == 0) {
			power_up_ = None;
			texture_ = default_tex_;
		}
	}
	else {
		health_--;
		time_since_hit_ = deltatime;
		texture_ = hurt_tex_;
		if (health_ == 0) {
			dead_ = true;
		}
	}
}

} // namespace game
