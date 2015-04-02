#include "Vector2D.h"

glm::vec2 makeVector2D(GLfloat x, GLfloat y){
    return glm::vec2{ x, y };
}

glm::vec2 addVector2D(glm::vec2 first, glm::vec2 second){
    return glm::vec2{ first.x + second.x, first.y + second.y };
}

glm::vec3 addVector3D(glm::vec3 first, glm::vec2 second){
    return glm::vec3{ first.x + second.x, first.y + second.y, first.z };
}