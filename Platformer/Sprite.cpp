#include "Sprite.h"

void Sprite::setPosition(Vector2D newPosition){
    position_ = newPosition;
}

Vector2D Sprite::getPosition(){
    return position_;
}

void Sprite::setRotation(GLfloat rotation){
    rotation_ = rotation;
}

GLfloat Sprite::getRotation(){
    return rotation_;
}

void Sprite::setVelocity(Vector2D newVector){
    velocity_ = newVector;
}

Vector2D Sprite::getVelocity(){
    return velocity_;
}

Sprite::Sprite(GLfloat textureBufferID, Vector2D position, int width, int height){
    textureBufferID_ = textureBufferID;
    position_ = position;
    width_ = width;
    height_ = height;
    velocity_ = makeVector2D(0.0f, 0.0f);
    rotation_ = 0;
}

void Sprite::render(){
    glBindTexture(GL_TEXTURE_2D, textureBufferID_);

    //Resets the Transformations
    glLoadIdentity();

    //Translate(move) the sprite to this position.
    glTranslatef(position_.x, position_.y, NULL);

    //Sets the angle of rotation for the sprite
    glRotatef(rotation_, NULL, NULL, 1.0f);
    glDrawArrays(GL_QUADS, 0, 4);
}

void Sprite::update(){
    position_ = addVector2D(position_, velocity_);
}