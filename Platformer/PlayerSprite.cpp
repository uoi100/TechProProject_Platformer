#include "PlayerSprite.h"

void PlayerSprite::checkInput(){
    int x = 0;
    int y = getVelocity().y;

    // If the right arrow key is pressed then move the character right
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS){
        if (!facingRight_){
            facingRight_ = true;
            
            model = glm::rotate(model,  (float) glm::radians(FLIP_HORIZONTAL_), glm::vec3(0.0f, 1.0f, 0.0f));
        }

            x += movementSpeed_;
    }

    // If the left array key is pressed then move the character left
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS){
        if (facingRight_){
            facingRight_ = false;

            model = glm::rotate(model, -(float)glm::radians(FLIP_HORIZONTAL_), glm::vec3(0.0f, 1.0f, 0.0f));
        }

            x -= movementSpeed_;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS && !jumping_ && !falling_){
        y = movementSpeed_;
        jumping_ = true;
        jumpCounter_ = jumpStrength_;
    }

    if (jumping_){
        y = movementSpeed_;

        jumpCounter_--;

        if (jumpCounter_ <= 0){
            jumping_ = false;
            setFalling(true);
        }
    }
    else if (falling_){
        y = -movementSpeed_;
    }

    setVelocity(glm::vec2(x, y));
}

PlayerSprite::PlayerSprite(GLfloat textureID, glm::vec2 position, glm::vec2 size, glm::vec2 windowSize)
:Sprite(textureID, position, size, windowSize){
}

void PlayerSprite::render(){
    Sprite::render();
}

void PlayerSprite::update(){

    Sprite::update();

    checkInput();
}

