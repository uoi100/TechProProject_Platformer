#include <GLFW\glfw3.h>

typedef struct{
    GLfloat x;
    GLfloat y;
} Vector2D;

class Sprite{
private:
    Vector2D position_; // position of the sprite
    GLfloat textureBufferID_; // texture id of the sprite
public:
    void setPosition( Vector2D newPosition);
    Vector2D getPosition();
    Sprite(GLfloat textureBufferID);
    void render();
    void update();
};