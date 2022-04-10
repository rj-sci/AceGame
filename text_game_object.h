#ifndef TEXT_GAME_OBJECT_H_
#define TEXT_GAME_OBJECT_H_

#include <string>

#include "game_object.h"
#include "collision.h"
#include "player_game_object.h"
namespace game {

    // Inherits from GameObject
    class TextGameObject : public GameObject {

        public:
            TextGameObject(const glm::vec3 &position, GLuint texture, PlayerGameObject* p);

            // Text to be displayed
            std::string GetText(void) const;
            void SetText(const std::string &text);

            // Render function for the text
            void Render(Shader &shader, glm::mat4 view_matrix, double current_time);
            bool ValidCollision(GameObject* other_game_object, double deltatime);
            bool HandleCollision(GameObject* other_game_object, double deltatime);

            inline void SetScale(const glm::vec2& text_scale) { text_scale_ = text_scale; }


        private:
            std::string text_;
            glm::vec2 text_scale_;
            PlayerGameObject* p_;

    }; // class TextGameObject

} // namespace game

#endif // TEXT_GAME_OBJECT_H_
