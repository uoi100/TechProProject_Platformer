#include "Prefix.h"
#ifndef SPRITE_H
#define SPRITE_H
#include "SpriteCollision.h"
class Sprite{
private:
    // Sprite Variables
    glm::vec2 velocity_;         // Movement of the sprite
    glm::vec2 fallHeight_;

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
    float const FLIP_HORIZONTAL_ = 180.0f;
    glm::vec3 position_;        // position of the sprite
    int width_;                 // Width of the Sprite
    int height_;                // Height of the Sprite
    int movementSpeed_;         // Speed of the Sprite when it moves
    int jumpStrength_;          // How high the sprite can jump
    int jumpCounter_;           // Counter that counts how high the Sprite should jump
    GLfloat rotation_;          // Rotation of the Sprite
    GLfloat rotationVelocity_;  // Velocity of the Rotation of the Sprite
    bool facingRight_;
    bool jumping_;
    bool falling_;
public:
    // Constructor Function
    Sprite(GLfloat textureID, glm::vec2 position, glm::vec2 size, glm::vec2 windowSize);

    // Getters and Setters
    void setPosition( glm::vec2 newPosition);
    glm::vec2 getPosition() const;

    void setRotation(int angle);
    GLfloat getRotation() const;

    void setRotationVelocity(GLfloat velocity);
    GLfloat getRotationVelocity() const;

    void setVelocity(glm::vec2 newVector);
    glm::vec2 getVelocity() const;

    void setJumping(bool jumping);
    bool getJumping() const;

    void setJumpStrength(int jumpStrength);
    bool getJumpStrength() const;

    void setFalling(bool falling);
    bool getFalling() const;

    glm::vec2 getFallHeight() const;

    void setSpeed(int speed);
    int getSpeed() const;

    int getWidth() const;
    int getHeight() const;

    glm::vec2 getSize();

    // Render and Update Functions
    virtual void render();
    virtual void update();
};

#endif