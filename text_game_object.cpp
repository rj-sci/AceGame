#include <glm/gtc/matrix_transform.hpp>

#include "text_game_object.h"

namespace game {

TextGameObject::TextGameObject(const glm::vec3 &position, GLuint texture, PlayerGameObject* p)
	: GameObject(position, texture, 0, false, 1.0) {
            text_ = "";
            p_ = p;
        }


void TextGameObject::Render(Shader &shader, glm::mat4 view_matrix, double current_time){

    // Bind the entity's texture
    glBindTexture(GL_TEXTURE_2D, texture_);

    // Set up the shader
    shader.Enable();
    shader.SetSpriteAttributes();

    // Setup the scaling matrix for the shader
    glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(text_scale_.x, text_scale_.y, 1.0));

    // Setup the rotation matrix for the shader
    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0, 0.0, 1.0));

    // Set up the translation matrix for the shader
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

    // Setup the transformation matrix for the shader
    glm::mat4 transformation_matrix = p_->GetParentTransformation() * translation_matrix * rotation_matrix * scaling_matrix;

    // Set the transformation matrix in the shader
    shader.SetUniformMat4("transformation_matrix", transformation_matrix);

    // Set the view matrix
    shader.SetUniformMat4("view_matrix", view_matrix);

    // Set the text
#define TEXT_LENGTH 13
    // Set text length
    int final_size = text_.size();
    if (final_size > TEXT_LENGTH){
        final_size = TEXT_LENGTH;
    }
    shader.SetUniform1i("text_len", final_size);

    // Set the text data
    GLint data[TEXT_LENGTH];
    for (int i = 0; i < final_size; i++){
        data[i] = text_[i];
    }
    shader.SetUniformIntArray("text_content", final_size, data);

    // Draw the entity
    glDrawElements(GL_TRIANGLES, shader.GetSpriteSize(), GL_UNSIGNED_INT, 0);
}


std::string TextGameObject::GetText(void) const {

    return text_;
}


void TextGameObject::SetText(const std::string &text){

    text_ = text;
}
bool TextGameObject::ValidCollision(GameObject* other_game_object, double deltatime) {
    return false;
}
bool TextGameObject::HandleCollision(GameObject* other_game_object, double deltatime) {
    return false;
}
} // namespace game
