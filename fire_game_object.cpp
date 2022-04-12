#include "fire_game_object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace game
{
	//Constructor
	FireGameObject::FireGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* p) : GameObject(position, texture, num_elements, true, 0.25)
	{
		target_ = p;
		rotation_ = 0.0f;
		scale_ = 1.0 / 2;
		name_ = laser;

		actualPosition_ = glm::vec3(0.0, 0.0, 0.0);


		orbit_angle_ = 0.0f;
	}


	//Update
	void FireGameObject::Update(double delta_time, double current_time)
	{
		float x = cos(rotation_ * (3.14159265 / 180));
		float y = sin(rotation_ * (3.14159265 / 180));

	

		orbit_angle_ += 360 * delta_time;


		SetPosition(glm::vec3(x, y, 0.0f));

		actualPosition_ = position_ + target_->GetPosition();



		//Update last time and current time
		last_t_ = current_t_;
		current_t_ += delta_time;


		rotation_ += 2.0f;

		if (rotation_ > 360)
		{
			rotation_ = rotation_ - 360;
		}
	}

	void FireGameObject::Render(Shader& shader, glm::mat4 view_matrix, double current_time)
	{
		// Bind the entity's texture
		glBindTexture(GL_TEXTURE_2D, texture_);

		// Setup the scaling matrix for the shader
		glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

		// Set up the translation matrix for the shader
		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);


		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), orbit_angle_, glm::vec3(0.0, 0.0, 1.0));



		// Setup the transformation matrix for the shader
		glm::mat4 transformation_matrix = target_->GetParentTransformation() * translation_matrix * rotation * scaling_matrix;
		//glm::mat4 transformation_matrix = scaling_matrix * translation_matrix * rotation * player_->GetParentTransformation();

		// TODO: Add other types of transformations

		// Set the transformation matrix in the shader
		shader.SetUniformMat4("transformation_matrix", transformation_matrix);
		//shader.SetUniformMat4("rotation_matrix", rotation_);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
	}
	bool FireGameObject::ValidCollision(GameObject* other_game_object, double deltatime) {
		switch (other_game_object->GetName()) {
		case player:
			return Collision::CircleCircleCollision(other_game_object, actualPosition_, radius_);
			break;
		}
	}
	bool FireGameObject::HandleCollision(GameObject* other_game_object, double deltatime) {
		return true;
	}
}
