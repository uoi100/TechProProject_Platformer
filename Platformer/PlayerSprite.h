#include "Prefix.h"
#include "Sprite.h"

class PlayerSprite : public Sprite{
private:
    void checkInput();
public:
    PlayerSprite(GLfloat textureID, glm::vec2 position, glm::vec2 size, glm::vec2 windowSize);

    void render();
    void update();
};