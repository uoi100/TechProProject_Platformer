#include <GLFW\glfw3.h>
#include "Vector2D.h"

class Sprite{
private:
    Vector2D velocity_; // Movement of the sprite
    GLfloat textureBufferID_; // texture id of the sprite
protected:
    Vector2D position_; // position of the sprite
    int width_;
    int height_;
public:
    void setPosition( Vector2D newPosition);
    Vector2D getPosition();
    void setVelocity(Vector2D newVector);
    Vector2D getVelocity();
    Sprite(GLfloat textureBufferID, Vector2D position, int width, int height);

    void render();
    virtual void update();
};