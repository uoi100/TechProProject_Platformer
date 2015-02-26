#include "PlayerSprite.h"

void PlayerSprite::setBoundingBox(BoundingBox boundingBox){
    boundingBox_ = boundingBox;
}

void PlayerSprite::getKeyInput(){
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP)
        && !jumping_ && !falling_)
        jumping_ = true;
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT)
        && position_.x >= boundingBox_.left + width_/2){
        position_ = addVector2D(position_, makeVector2D(-4.0f, 0.0f));
        facingRight_ = false;
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT)
        && position_.x <= boundingBox_.right - width_/2){
        position_ = addVector2D(position_, makeVector2D(4.0f, 0.0f));
        facingRight_ = true;
    }
}

PlayerSprite::PlayerSprite(GLuint textureBufferID, Vector2D position, int width, int height)
:Sprite(textureBufferID, position, width, height){
    falling_ = true;
    jumping_ = false;
    maxJumpHeight = 100;
    currentJumpHeight = 0;
}

void PlayerSprite::render(){
    glBindTexture(GL_TEXTURE_2D, textureBufferID_);

    //Resets the Transformations
    glLoadIdentity();

    //Translate the origin of the image to be rotated, in this case its center
    //Translate the image to x + center of width
    //Translate the image to y + center of height
    glTranslatef(position_.x, position_.y, NULL);
    //Sets which angle the player will be facing
    if (facingRight_)
        glRotatef(180, NULL, 180, 1.0f);    
    else
        glRotatef(rotation_, NULL, NULL, 1.0f);
    //Undo the translation of the origin    

    glDrawArrays(GL_QUADS, 0, 4);
}

void PlayerSprite::update(){
    getKeyInput();
    if (jumping_){
        position_ = addVector2D(position_, makeVector2D(0.0f, 5.0f));
        if (currentJumpHeight < maxJumpHeight){
            currentJumpHeight+= 5;
        }
        else
        {
            jumping_ = false;
            falling_ = true;
        }
    }
    if (falling_){
        if (position_.y - height_/2 < boundingBox_.bottom){
            falling_ = false;
            currentJumpHeight = 0;
            position_.y = 0 + height_/2;
        }
        else
        position_ = addVector2D(position_, makeVector2D(0.0f, -5.0f));
    }
}

