#include "Prefix.h"

class Sprite{
private:
    Vector2D velocity_; // Movement of the sprite
protected:
    GLfloat textureBufferID_; // texture id of the sprite
    Vector2D position_; // position of the sprite
    int width_;
    int height_;
    GLfloat rotation_;
    GLfloat rotationVelocity_;
public:
    void setPosition( Vector2D newPosition);
    Vector2D getPosition();
    void setRotation(GLfloat rotation);
    GLfloat getRotation();
    void setRotationVelocity(GLfloat velocity);
    GLfloat getRotationVelocity();
    void setVelocity(Vector2D newVector);
    Vector2D getVelocity();
    int getWidth();
    int getHeight();

    Sprite(GLfloat textureBufferID, Vector2D position, int width, int height);

    virtual void render();
    virtual void update();
};