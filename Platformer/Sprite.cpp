#include "Sprite.h"

void Sprite::setPosition(Vector2D newPosition){
    position_ = newPosition;
}

Vector2D Sprite::getPosition(){
    return position_;
}

Sprite::Sprite(GLfloat textureBufferID) : textureBufferID_{ textureBufferID }{
}

void Sprite::render(){
    glBindTexture(GL_TEXTURE_2D, textureBufferID_);

    glDrawArrays(GL_QUADS, 0, 4);
}

void Sprite::update(){

}