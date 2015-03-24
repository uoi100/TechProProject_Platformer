#include "Prefix.h"
#include "Sprite.h"

class PlayerSprite : public Sprite{
private:
    BoundingBox boundingBox_;
    bool falling_;
    bool jumping_;
    GLfloat maxJumpHeight;
    GLfloat currentJumpHeight;
    GLfloat facingRight_;

    void getKeyInput();
public:
    void setBoundingBox(BoundingBox boundingBox);

    PlayerSprite(GLfloat textureID, glm::vec2 position, glm::vec2 size, glm::vec2 windowSize);

    void render();
    void update();
};