#include "laser_game_object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace game
{
	LaserGameObject::LaserGameObject(const glm::vec3& position, GLuint texture, GLint num_elements, GameObject* p) : GameObject(position, texture, num_elements, true, 0.5)
	{
		target_ = p;
		rotation_ = 0.0f;
		scale_ = 1.0 / 2;
		name_ = laser;
	}

	void LaserGameObject::Update(double delta_time)
	{
		float x = cos(rotation_ * (3.14159265 / 180));
		float y = sin(rotation_ * (3.14159265 / 180));


		SetPosition(glm::vec3(x, y, 0.0f));



		rotation_ += 2.0f;

		if (rotation_ > 360)
		{
			rotation_ = rotation_ - 360;
		}
	}

	void LaserGameObject::Render(Shader& shader)
	{
		// Bind the entity's texture
		glBindTexture(GL_TEXTURE_2D, texture_);

		// Setup the scaling matrix for the shader
		glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

		// Set up the translation matrix for the shader
		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));


		// Setup the transformation matrix for the shader
		glm::mat4 transformation_matrix = target_->GetParentTransformation() * translation_matrix * scaling_matrix;
		//glm::mat4 transformation_matrix = scaling_matrix * translation_matrix * rotation * player_->GetParentTransformation();

		// TODO: Add other types of transformations

		// Set the transformation matrix in the shader
		shader.SetUniformMat4("transformation_matrix", transformation_matrix);
		//shader.SetUniformMat4("rotation_matrix", rotation_);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
	}
}
