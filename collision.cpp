#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "collision.h"
int game::Collision::FindCollisions(std::vector<GameObject*>* game_objects_, game::GameObject* current_game_object){
    glm::vec3 position = {};
    // Check for collision with other game objects
    int vecsize_ = game_objects_->size();
    for (int j = 1; j < vecsize_; j++) {
        GameObject* other_game_object = (*game_objects_)[j];
        float distance = glm::length(current_game_object->GetPosition() - other_game_object->GetPosition());
        float radii_sum = current_game_object->GetRadius() + other_game_object->GetRadius();
        if (radii_sum > distance) {
            position = current_game_object->GetPosition();
            float x_length = position.x;
            float y_length = position.y;
            float z_length = position.z;
            return j;
        }
    }
}
