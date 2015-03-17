#include "Screen.h"

Screen::Screen(int width, int height){
width_ = width;
height_ = height;
switchScreen_ = false;
screenIndex_ = 0;
}

bool Screen::switchScreen(){
    return switchScreen_;
}

int Screen::screenIndex(){
    return screenIndex_;
}

void Screen::mouseEvent(int button, int action){}
void Screen::render(){}
void Screen::update(){}