#include "Vector2D.h"

Vector2D makeVector2D(GLfloat x, GLfloat y){
    return Vector2D{ x, y };
}

Vector2D addVector2D(Vector2D first, Vector2D second){
    return Vector2D{ first.x + second.x, first.y + second.y };
}