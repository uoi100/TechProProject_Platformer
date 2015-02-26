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

    PlayerSprite(GLuint textureBufferID, Vector2D position, int width, int height);

    void render();
    void update();
};