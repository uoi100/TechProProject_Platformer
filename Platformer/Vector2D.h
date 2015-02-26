#include <GLFW\glfw3.h>

typedef struct{
    GLfloat x;
    GLfloat y;
} Vector2D;

Vector2D makeVector2D(GLfloat x, GLfloat y);
Vector2D addVector2D(Vector2D first, Vector2D second);