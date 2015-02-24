#include <GLFW\glfw3.h>
#include "Vector2D.h"

class Sprite{
private:
    Vector2D position_; // position of the sprite
    Vector2D velocity_; // Movement of the sprite
    GLfloat textureBufferID_; // texture id of the sprite
public:
    void setPosition( Vector2D newPosition);
    Vector2D getPosition();
    void setVelocity(Vector2D newVector);
    Vector2D getVelocity();
    Sprite(GLfloat textureBufferID, Vector2D position);

    void render();
    void update();
};