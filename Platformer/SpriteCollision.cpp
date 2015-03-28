#include "SpriteCollision.h"

bool checkCollision(Sprite* a, Sprite* b){
    // Get the offset between point A and point B
    int result = abs(a->getPosition().x - b->getPosition().x) + abs(a->getPosition().y - b->getPosition().y);

    // Get the offset required to determine if a collision happens or not
    int range = a->getWidth() / 2 + a->getHeight() / 2 + b->getWidth() / 2 + b->getHeight() / 2;

    // If the result is equal or below the range then a collision occured
    if (result <= range)
        return true;
    return false;
}

bool collideSides(Sprite* a, Sprite* b, bool* rightSideCollide, int* offsetX){
    // Get the position of both sprites
    int x1, x2, y1, y2;
    x1 = a->getPosition().x;
    x2 = b->getPosition().x;
    y1 = a->getPosition().y;
    y2 = b->getPosition().y;

    // Get the offset of collisions on each side
    int leftSide, rightSide;
    leftSide = abs((x1 - a->getWidth() / 2) - (x2 + b->getWidth() / 2));
    rightSide = abs((x1 + a->getWidth() / 2) - (x2 - b->getWidth() / 2));

    // Get the x offset between point A and point B
    int result = abs(a->getPosition().x - b->getPosition().x);

    // Get the offset required to determine if a collision happens or not
    int range = a->getWidth() / 2 + b->getWidth() / 2;

    // If the result is equal or below the range then a collision occured
    if (result <= range){
        if (rightSide < leftSide){
            if (rightSideCollide != NULL)
                *rightSideCollide = true;
            if(offsetX != NULL)
                *offsetX = rightSide;
        } else {
            if (rightSideCollide != NULL)
                *rightSideCollide = false;
            if (offsetX != NULL)
               *offsetX = leftSide;
        }
        return true;
    }
    
    return false;
}

bool collideBottom(Sprite* a, Sprite* b, int* offsetY){
    // Get the y offset between point A and Point B
    int result = abs((a->getPosition().y - a->getHeight() / 2) - (b->getPosition().y + b->getHeight() / 2));

    // Get the offset required to determine if a collision happens or not
    int range = a->getHeight() / 2 + b->getHeight() / 2;

    // If the result is equal or below the range then a collision occured
    if (result <= range){
        if (offsetY != NULL)
            *offsetY = result;
        return true;
    }
    return false;
}

/*
 *@return true if 1 point from one sprite is between 2 points of the other sprite
 */
bool between(Sprite* a, Sprite* b){
    glm::vec2 aXPos(a->getPosition().x - a->getWidth() / 2, a->getPosition().x + a->getWidth() / 2);
    glm::vec2 bXPos(b->getPosition().x - b->getWidth() / 2, b->getPosition().x + b->getWidth() / 2);

    return (aXPos.x < bXPos.x && bXPos.x < aXPos.y) ||
        (aXPos.x < bXPos.y && bXPos.y < aXPos.y) ||
        (bXPos.x < aXPos.x && aXPos.x < bXPos.y) ||
        (bXPos.x < aXPos.y && aXPos.y < bXPos.y);
}

/*
 * Check if (x,y) is inside this sprite
 */
bool pointInsideSprite(Sprite* a, int x, int y){
    glm::vec2 pos = a->getPosition();
    int width = a->getWidth() / 2;
    int height = a->getHeight() / 2;
    int x1 = pos.x - width;
    int x2 = pos.x + width;
    int y1 = pos.y - height;
    int y2 = pos.y + height;    

    return (x1 < x && x < x2) && (y1 < y && y < y2);
}