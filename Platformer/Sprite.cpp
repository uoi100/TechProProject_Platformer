#include "Sprite.h"

void Sprite::setPosition(Vector2D newPosition){
    position_ = newPosition;
}

Vector2D Sprite::getPosition(){
    return position_;
}

Sprite::Sprite(GLfloat textureBufferID, Vector2D position){
    textureBufferID_ = textureBufferID;
    position_ = position;
}

void Sprite::render(){
    glBindTexture(GL_TEXTURE_2D, textureBufferID_);

    //Resets the Transformations
    glLoadIdentity();
    //Translate(move) the sprite to this position.
    glTranslatef(position_.x, position_.y, NULL);

    glDrawArrays(GL_QUADS, 0, 4);
}

void Sprite::update(){

}