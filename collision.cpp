#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "collision.h"
bool game::Collision::FindCollisions(int i, std::vector<GameObject*>* game_objects_, game::GameObject* current_game_object, double deltatime) {
    // Check for collision with other game objects
    int vecsize_ = game_objects_->size();
    for (int j = 1; j < vecsize_; j++) {
        GameObject* other_game_object = (*game_objects_)[j];
        if (j != i && current_game_object->ValidCollision(other_game_object, deltatime) == true) {
            double time = glfwGetTime();
            current_game_object->HandleCollision(other_game_object, deltatime);
            other_game_object->HandleCollision(current_game_object, deltatime);
        }
    }
    return 0;
}