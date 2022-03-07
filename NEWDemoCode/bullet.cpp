#include "bullet.h"
#include <math.h>

namespace game {
	Bullet::Bullet(const glm::vec3& position, GLuint texture, GLint num_elements, double damage, float rotation, float time):
		GameObject(position, texture, num_elements,true, 0.5, "bullet") {
		damage_ = damage;
        rotation_ = rotation;
        time_ = time;
        timer = 0;
	}

	void Bullet:: Update(double delta_time) {
        double radians = ((2 * 3.1415926536 / 360) * (rotation_ + 90));
        velocity_[0] = cos(radians) * BULLET_SPEED;
        velocity_[1] = sin(radians) * BULLET_SPEED;
        if (glfwGetTime() - time_ > BULLET_EXPIRY) {
            dead_ = true;
        }
        //TO-D0:Caclulate ray vector
        /*The ray vector(w.r.t time) is:

        Vector algebra equation for circle:
        | C - X | = r
        (C - X) dot (C - X) = r^2
        Plug in ray equation:
        - X = P + td
        into:
        at^2 + bt + c = 0
        and use quadratic equation to get # of t's.
        IF:
        t has increased, there has been a collision.
        else, no collision has happened.  
        and isolate t, and examine its values
        * */
        GameObject::Update(delta_time);
	}

	void Bullet::Render(Shader& shader) {
        // Bind the entity's texture
        glBindTexture(GL_TEXTURE_2D, texture_);

        // Setup the scaling matrix for the shader
        glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1.0));

        // Set up the translation matrix for the shader
        glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

        //rotation matrix
        glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));

        // Setup the transformation matrix for the shader
        glm::mat4 transformation_matrix = translation_matrix * rotation_matrix * scaling_matrix;

        // Set the transformation matrix in the shader
        shader.SetUniformMat4("transformation_matrix", transformation_matrix);

        // Draw the entity
        glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
	}
    void Bullet::Destroy() {
        GameObject::Destroy();
    }
    bool Bullet::ValidCollision(GameObject* other_game_object) {
        if (other_game_object->GetName() == "enemy") {
            /*
            float distance = glm::length(position_ - other_game_object->GetPosition());
            double radians = ((2 * 3.1415926536 / 360) * (rotation_ + 90));
            float r2 = pow(distance, 2);
            float a = glm::dot(velocity_, velocity_);
            float b = glm::dot(velocity_ * 2.0f, position_ - other_game_object->GetPosition());
            float c = glm::dot(position_ - other_game_object->GetPosition(), position_ - other_game_object->GetPosition()) - r2;
            float discr = pow(b, 2) - (4 * a * c);
            */
            return true;
        }return false;
    }
}