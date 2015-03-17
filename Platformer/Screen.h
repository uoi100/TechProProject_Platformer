#include "Prefix.h"

#ifndef SCREEN_H
#define SCREEN_H

class Screen{
protected:
    int width_;
    int height_;
    bool switchScreen_;
    int screenIndex_;
public:
    Screen(int width, int height);
    bool switchScreen();
    int screenIndex();

    void virtual mouseEvent(int button, int action);
    void virtual render();
    void virtual update();
};

#endif