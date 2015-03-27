#ifndef SPRITECOLLISION_H
#define SPRITECOLLISION_H
#include "Prefix.h"
#include "Sprite.h"

bool checkCollision(Sprite* a, Sprite* b);
bool collideSides(Sprite* a, Sprite* b, bool* rightSideCollide = NULL, int* offsetX = NULL);
bool collideBottom(Sprite* a, Sprite* b, int* offsetY = NULL);

#endif