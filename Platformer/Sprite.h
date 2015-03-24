#include "Prefix.h"
#ifndef SPRITE_H
#define SPRITE_H

class Sprite{
private:
    // Sprite Data
    glm::vec2 velocity_;         // Movement of the sprite

    // Matrix Transformation Function
    void matrixTransformation();
protected:
    // Matrix Transformation Variables
    float const HORIZONTAL_ANGLE_ = 3.14f;    // The angle is towards -Z
    float const VERTICAL_ANGLE_ = 0.0f;       // The angle is 0, to look at the horizon
    float const PI_ = 3.14;
    float const ZNEAR = -1.0f;
    float const ZFAR = 100.0f;
    glm::vec3 direction;                    // Direction you look at
    glm::vec3 up;                           // The angle you're looking at
    // Matrix Movements
    glm::vec3 moveRight;
    glm::vec3 moveUp;
    // Matrices
    glm::mat4 projection;
    glm::mat4 model;

    // Texture Data
    GLfloat textureID_;         // texture id of the sprite

    // Sprite Variables
    glm::vec3 position_;        // position of the sprite
    int width_;                 // Width of the Sprite
    int height_;                // Height of the Sprite
    GLfloat rotation_;          // Rotation of the Sprite
    GLfloat rotationVelocity_;  // Velocity of the Rotation of the Sprite
public:
    // Constructor Function
    Sprite(GLfloat textureID, glm::vec2 position, glm::vec2 size, glm::vec2 windowSize);

    // Getters and Setters
    void setPosition( glm::vec2 newPosition);
    glm::vec2 getPosition();

    void setRotation(GLfloat rotation);
    GLfloat getRotation();

    void setRotationVelocity(GLfloat velocity);
    GLfloat getRotationVelocity();

    void setVelocity(glm::vec2 newVector);
    glm::vec2 getVelocity();

    int getWidth();
    int getHeight();

    // Render and Update Functions
    virtual void render();
    virtual void update();
};

#endif