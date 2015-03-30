#include "PlayerSprite.h"
#include <algorithm>

enum Direction { LEFT, RIGHT, UP, DOWN };

struct findClosest{
    // Comparison Variables
    int xOffset_;
    int yOffset_;
    int min_;
    Direction direction_;

    // Source Variables
    int leftSide_;
    int rightSide_;
    int bottomSide_;
    int topSide_;
    // We store the closest match here
    Sprite* closest;

    // location of the side of the player and direction
    findClosest(Sprite* source, Direction direction){
        // We make this the largest possible value so we can find the smallest value for comparison
        min_ = INT16_MAX;
        xOffset_ = INT16_MAX;
        yOffset_ = INT16_MAX;
        direction_ = direction;

        // Get the coordinates of the source's sides
        glm::vec2 pos = source->getPosition();
        int width = source->getWidth() / 2;
        int height = source->getHeight() / 2;

        leftSide_ = pos.x - width;
        rightSide_ = pos.x + width;
        topSide_ = pos.y + height;
        bottomSide_ = pos.y - height;
    }

    // Determine the sprite with the lowest offset depending on which side
    void operator()(Sprite* a){
        int width = a->getWidth() / 2;
        int height = a->getHeight() / 2;

        glm::vec2 pos = a->getPosition();

        int leftSide = pos.x - width;
        int rightSide = pos.x + width;
        int bottomSide = pos.y - height;
        int topSide = pos.y + height;

        int xOffset = abs(leftSide_ - rightSide) + abs(rightSide_ - leftSide);
        int yOffset = abs(topSide_ - bottomSide) + abs(bottomSide_ - topSide);

        int offset = xOffset + yOffset;

        if (direction_ == LEFT || direction_ == RIGHT){
            if (bottomSide_ > topSide)
                return;
        }

        if (offset < min_){
            min_ = offset;
            closest = a;
        }
    }

};

void PlayerSprite::checkInput(){
    int x = 0;
    int y = getVelocity().y;
    bool nearbyObjects = objects_.size() > 0;

    int playerRight = position_.x + width_ / 2;
    int playerLeft = position_.x - width_ / 2;
    int playerBottom = position_.y - height_ / 2;
    int playerTop = position_.y + height_ / 2;

    // If the right arrow key is pressed then move the character right
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS){
        if (!facingRight_){
            facingRight_ = true;

            model = glm::rotate(model, (float)glm::radians(FLIP_HORIZONTAL_), glm::vec3(0.0f, 1.0f, 0.0f));
        }

        x += movementSpeed_;

        if (nearbyObjects){
            // check if there is an object on the player's line of path
            for (Sprite *object : objects_){
                bool collide = false;

                for (int i = 0; i <= height_; i++){
                    if (pointInsideSprite(object, playerRight + movementSpeed_, playerBottom + i))
                    {
                        x = 0;
                        collide = true;
                        position_.x = object->getPosition().x - object->getWidth() / 2 - width_ / 2;
                        break;
                    }
                }

                if (collide){
                    break;
                }
            }
        }
    }

    // If the left array key is pressed then move the character left
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS){
        if (facingRight_){
            facingRight_ = false;

            model = glm::rotate(model, -(float)glm::radians(FLIP_HORIZONTAL_), glm::vec3(0.0f, 1.0f, 0.0f));
        }

        x -= movementSpeed_;

        if (nearbyObjects){
            // check if there is an object on the player's line of path
            for (Sprite *object : objects_){
                bool collide = false;

                for (int i = 0; i <= height_; i++){
                    if (pointInsideSprite(object, playerLeft - movementSpeed_, playerBottom + i))
                    {
                        x = 0;
                        collide = true;
                        position_.x = object->getPosition().x + object->getWidth() / 2 + width_ / 2;
                        break;
                    }
                }

                if (collide){
                    break;
                }
            }
        }
    }

    // Player Jumps up
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS && !jumping_ && !falling_){
        y = movementSpeed_;
        jumping_ = true;
        jumpCounter_ = jumpStrength_;
    }

    // Gravity Logic
    // Check if the player is on the ground
    if (!nearbyObjects){
        if (position_.y - height_ / 2 > 0){
            setFalling(true);
        }
    }
    else {
        bool collide = false;
        for (Sprite *object : objects_){
            for (int i = 0; i < width_ - 5; i++){
                if (pointInsideSprite(object, playerLeft + i, playerBottom - movementSpeed_))
                {
                    collide = true;
                    position_.y = object->getPosition().y + object->getHeight() / 2 + height_ / 2;
                    break;
                }
            }

            if (collide){
                break;
            }
        }
        if (!collide){
            setFalling(true);
        }
    }

    // Check if the player is still jumping
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


        if (nearbyObjects){
            // check if there is an object on the player's line of path
            for (Sprite *object : objects_){
                bool collide = false;

                for (int i = 0; i < width_ - 5; i++){
                    if (pointInsideSprite(object, playerLeft + i, playerBottom - movementSpeed_))
                    {
                        y = 0;
                        setFalling(false);
                        collide = true;
                        break;
                    }
                }

                if (collide){
                    break;
                }
            }
            

        }

        if (position_.y - height_/2 < 0){
            y = 0;
            setFalling(false);
        }
    }

    objects_.clear();
    setVelocity(glm::vec2(x, y));
}

PlayerSprite::PlayerSprite(GLfloat textureID, glm::vec2 position, glm::vec2 size, glm::vec2 windowSize)
:Sprite(textureID, position, size, windowSize){
}

void PlayerSprite::setObjects(std::vector<Sprite*> objects){
    objects_ = objects;
}

void PlayerSprite::render(){
    Sprite::render();
}

void PlayerSprite::update(){

    Sprite::update();

    checkInput();

    if (falling_)
        OutputDebugString("Falling\n");
    else
        OutputDebugString("Not Falling\n");
}

