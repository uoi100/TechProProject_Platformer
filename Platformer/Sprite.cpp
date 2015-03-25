#include "Sprite.h"

// Matrix Transformation Function
/*
 *@Description: Matrix Transformations
    these matrices determine how the sprite will be drawn on the screen
 */
void Sprite::matrixTransformation(){
    // The Matrix that contains information:
    // Where the camera is
    // Where the camera is looking at
    // The angle the camera is looking at
    glm::mat4 view = glm::lookAt(
        position_,
        position_ + direction,
        up
    );

    // Projection View Model
    glm::mat4 mvp = projection * view * model;

    // Get our program pointer
    GLint programID;
    glGetIntegerv(GL_CURRENT_PROGRAM, &programID);

    // Get the pointer location of the variable "mvp" in the program
    GLuint matrixID = glGetUniformLocation(programID, "mvp");

    // Apply our Matrix Transformation
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(mvp));
}

/*
 *@Description: Sprite Class Constructor
 *@textureID - Pointer to the texture data that the sprite will display
 *@position - Position on the screen where the sprite will be
 *@windowSize - Size of the window context
 */
Sprite::Sprite(GLfloat textureID, glm::vec2 position, glm::vec2 size, glm::vec2 windowSize){
    // Setup Matrix Variables
    direction = glm::vec3(
        cos(VERTICAL_ANGLE_) * sin(HORIZONTAL_ANGLE_),
        sin(VERTICAL_ANGLE_),
        cos(VERTICAL_ANGLE_) * cos(HORIZONTAL_ANGLE_)
    );
    up = glm::vec3(0, 1, 0);

    // Setup Movements
    moveRight = glm::vec3(
        sin(HORIZONTAL_ANGLE_ + PI_ / 2.0f),
        0,
        0
    );

    moveUp = glm::vec3(
        0,
        cos(VERTICAL_ANGLE_),
        0
    );

    // Setup Matrices
    projection = glm::ortho(0.0f, -(float)windowSize.x, 0.0f, -(float)windowSize.y, ZNEAR, ZFAR);
    model = glm::mat4(1.0f);

    // Setup Sprite Variables
    textureID_ = textureID;
    position_ = glm::vec3(position.x, position.y, 3);
    width_ = size.x;
    height_ = size.y;
    velocity_ = glm::vec2(0.0f, 0.0f);
    rotation_ = 0;
}

// Getters and Setters

void Sprite::setPosition(glm::vec2 newPosition){
    position_.x = newPosition.x;
    position_.y = newPosition.y;
}

glm::vec2 Sprite::getPosition(){
    return glm::vec2(position_.x, position_.y);
}

void Sprite::setRotation(GLfloat rotation){
    rotation_ = rotation;
}

GLfloat Sprite::getRotation(){
    return rotation_;
}

void Sprite::setRotationVelocity(GLfloat velocity){
    rotationVelocity_ = velocity;
}

GLfloat Sprite::getRotationVelocity(){
    return rotationVelocity_;
}

void Sprite::setVelocity(glm::vec2 newVector){
    velocity_ = newVector;
}

glm::vec2 Sprite::getVelocity(){
    return velocity_;
}

int Sprite::getWidth(){
    return width_;
}

int Sprite::getHeight(){
    return height_;
}

// Render and Update Functions

void Sprite::render(){

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID_);
    matrixTransformation();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Draw the vertices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

void Sprite::update(){
    // Update our sprite position
    position_.x += velocity_.x;
    position_.y += velocity_.y;

    rotation_ += rotationVelocity_;
}