#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "collision.h"
bool game::Collision::FindCollisions(int i, std::vector<GameObject*>* game_objects_, game::GameObject* current_game_object) {
    glm::vec3 position = {};
    // Check for collision with other game objects
    int vecsize_ = game_objects_->size();
    float radii;
    float distance;
    for (int j = 1; j < vecsize_; j++) {
        GameObject* other_game_object = (*game_objects_)[j];
        distance = glm::length(current_game_object->GetPosition() - other_game_object->GetPosition());
        radii = other_game_object->GetRadius() + current_game_object->GetRadius();
        if ( j != i && distance < radii && current_game_object->ValidCollision(other_game_object)) {
            double death_time = glfwGetTime();
            current_game_object->SetDeathTime(death_time);
            other_game_object->SetDeathTime(death_time);
            current_game_object->Destroy();
            other_game_object->Destroy();
        }
    }
    return 0;
}