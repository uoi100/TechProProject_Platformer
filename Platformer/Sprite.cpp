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
    rotationVelocity_ = 1;
    facingRight_ = false;
    movementSpeed_ = 0;
    jumping_ = false;
    falling_ = false;
    jumpCounter_ = 0;
    jumpStrength_ = 0;
}

// Getters and Setters

void Sprite::setPosition(glm::vec2 newPosition){
    position_.x = newPosition.x;
    position_.y = newPosition.y;
}

glm::vec2 Sprite::getPosition() const{
    return glm::vec2(position_.x, position_.y);
}

void Sprite::setRotation(int angle){
    rotation_ = (float)angle / (float)100;
}

GLfloat Sprite::getRotation() const{
    return rotation_;
}

void Sprite::setRotationVelocity(GLfloat velocity){
    rotationVelocity_ = velocity;
}

GLfloat Sprite::getRotationVelocity() const{
    return rotationVelocity_;
}

void Sprite::setVelocity(glm::vec2 newVector){
    velocity_ = newVector;
}

glm::vec2 Sprite::getVelocity() const{
    return velocity_;
}

void Sprite::setJumping(bool jumping){
    jumping_ = jumping;
}

bool Sprite::getJumping() const{
    return jumping_;
}

void Sprite::setJumpStrength(int jumpStrength){
    jumpStrength_ = jumpStrength;
}

bool Sprite::getJumpStrength() const{
    return jumpStrength_;
}

void Sprite::setFalling(bool falling){
    if (falling)
        fallHeight_ = makeVector2D(position_.x, position_.y);
    else{
        setVelocity(makeVector2D(getVelocity().x, 0));
        fallHeight_ = glm::vec2(0, 0);
        setJumping(false);
    }

    falling_ = falling;
}

bool Sprite::getFalling() const{
    return falling_;
}

glm::vec2 Sprite::getFallHeight() const{
    return fallHeight_;
}

void Sprite::setSpeed(int speed){
    movementSpeed_ = speed;
}

int Sprite::getSpeed() const{
    return movementSpeed_;
}

int Sprite::getWidth() const{
    return width_;
}

int Sprite::getHeight() const{
    return height_;
}

glm::vec2 Sprite::getSize(){
    return glm::vec2(width_, height_);
}

// Render and Update Functions

void Sprite::render(int xOffset, int yOffset){

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID_);

    position_.x += xOffset;
    position_.y += yOffset;
    // Perform Matrix Calculations
    matrixTransformation();

    position_.x -= xOffset;
    position_.y -= yOffset;

    // Apply Alpha-Blending so that our images have transparent background
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw the vertices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

void Sprite::update(){
    // Update our sprite position
    position_.x += velocity_.x;
    position_.y += velocity_.y;

    model = glm::rotate(model, rotation_ * rotationVelocity_, glm::vec3(0, 0, 1.0f));

}