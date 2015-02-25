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

int Sprite::getWidth(){
    return width_;
}

int Sprite::getHeight(){
    return height_;
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

    //Translate the origin of the image to be rotated, in this case its center
    //Translate the image to x + center of width
    //Translate the image to y + center of height
    glTranslatef(position_.x+width_/2, position_.y+height_/2, NULL);
    //Sets the angle of rotation for the sprite
    glRotatef(rotation_, NULL, NULL, 1.0f);
    //Undo the translation of the origin
    glTranslatef( -width_/2,-height_/2, NULL);

    glDrawArrays(GL_QUADS, 0, 4);
}

void Sprite::update(){
    position_ = addVector2D(position_, velocity_);
}