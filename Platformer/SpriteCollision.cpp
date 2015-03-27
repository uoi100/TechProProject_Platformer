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