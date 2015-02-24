#include "PlayerSprite.h"

void PlayerSprite::setBoundingBox(BoundingBox boundingBox){
    boundingBox_ = boundingBox;
}

PlayerSprite::PlayerSprite(GLuint textureBufferID, Vector2D position, int width, int height)
:Sprite(textureBufferID, position, width, height){

}

void PlayerSprite::update(){
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP)
        && position_.y <= boundingBox_.top - height_)
        position_ = addVector2D(position_, makeVector2D(0.0f, 4.0f));
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN)
        && position_.y >= boundingBox_.bottom)
        position_ = addVector2D(position_, makeVector2D(0.0f, -4.0f));
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT)
        && position_.x >= boundingBox_.left)
        position_ = addVector2D(position_, makeVector2D(-4.0f, 0.0f));
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT)
        && position_.x <= boundingBox_.right - width_)
        position_ = addVector2D(position_, makeVector2D(4.0f, 0.0f));

    rotation_ -= 35;
}

