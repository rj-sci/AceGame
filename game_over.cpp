
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "game_over.h"

namespace game
{

	//Constructor for Game Over object
	GameOver::GameOver(const glm::vec3& position, GLuint texture, GLint num_elements, bool collidable_, float radius)
		: GameObject(position, texture, num_elements, collidable_, radius) {

		scale_ = 10.0;
	}

	GameOver::~GameOver()
	{

	}

	void GameOver::Update(double delta_time, double current_time)
	{

	}

	//Render
	void GameOver::Render(Shader& shader, glm::mat4 view_matrix, double current_time) {

		// Bind the entity's texture
		glBindTexture(GL_TEXTURE_2D, texture_);

		// Setup the scaling matrix for the shader
		glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

		//glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0, 0.0, 1.0));

		// Set up the translation matrix for the shader
		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);


		// Setup the transformation matrix for the shader
		glm::mat4 transformation_matrix = translation_matrix * scaling_matrix;

		// Set the transformation matrix in the shader
		shader.SetUniformMat4("transformation_matrix", transformation_matrix);

		shader.SetUniformMat4("view_matrix", view_matrix);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
	}

	bool GameOver::ValidCollision(GameObject* other_game_object, double deltatime)
	{
		return false;
	}
	bool GameOver::HandleCollision(GameObject* other_game_object, double deltatime)
	{
		return false;
	}
}