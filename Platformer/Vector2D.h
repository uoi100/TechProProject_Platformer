#ifndef VECTOR2D_H
#define VECTOR2D_H
#include "Prefix.h"

glm::vec2 makeVector2D(GLfloat x, GLfloat y);
glm::vec2 addVector2D(glm::vec2 first, glm::vec2 second);
glm::vec3 addVector3D(glm::vec3 first, glm::vec2 second);
#endif