#include "Prefix.h"
#include "Sprite.h"

class PlayerSprite : public Sprite{
private:
    void checkInput();
    std::vector<Sprite *> objects_;
public:
    PlayerSprite(GLfloat textureID, glm::vec2 position, glm::vec2 size, glm::vec2 windowSize);

    // Get objects near the player
    void setObjects(std::vector<Sprite *> objects);

    void render();
    void update();
};