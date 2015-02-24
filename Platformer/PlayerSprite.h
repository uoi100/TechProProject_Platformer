#include "Sprite.h"
#include "BoundingBox.h"

class PlayerSprite : public Sprite{
private:
    BoundingBox boundingBox_;
public:
    void setBoundingBox(BoundingBox boundingBox);

    PlayerSprite(GLuint textureBufferID, Vector2D position, int width, int height);

    void update();
};