#include "TitleScreen.h"
#include <sstream>

/*
 * @Author Calvin Truong Wesley Dale
 * @Version 1.0
 * @Description
 */
bool TitleScreen::checkButtonCollision(int xpos, int ypos, Sprite* btn){
    return (xpos >= btn->getPosition().x - btn->getWidth() / 2 &&
        xpos <= btn->getPosition().x + btn->getWidth() / 2 &&
        ypos >= btn->getPosition().y - btn->getHeight() / 2 &&
        ypos <= btn->getPosition().y + btn->getHeight() / 2);
}

TitleScreen::TitleScreen(int width, int height): Screen(width,height){
    createVertexBuffer(&menuButtonVAOID_, &menuButtonVBOID_, 300, 100);

    startBtnID_ = loadAndBufferImage("./Image/Start.png");
    exitBtnID_ = loadAndBufferImage("./Image/Exit.png");

    startBtn_ = new Sprite(startBtnID_, makeVector2D(width_ / 2, height_ / 2), 300, 100);
    exitBtn_ = new Sprite(startBtnID_, makeVector2D(width_ / 2, height_ / 2 - 200), 300, 100);
}

TitleScreen::~TitleScreen(){
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete startBtn_;
    delete exitBtn_;
    glDeleteBuffers(1, &menuButtonVBOID_);
    glDeleteVertexArrays(1, &menuButtonVAOID_);
    glDeleteTextures(1, &startBtnID_);
    glDeleteTextures(1, &exitBtnID_);
}

/*
 * Description: When the mouse is clicked, if there is a button
 * at the location that was clicked, do the following:
 * Start - Start the game
 * Exit - Exit the game
 */
void TitleScreen::mouseEvent(int button, int action){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);
        ypos = height_ - ypos;

        std::stringstream ss;
        std::string line;
        ss << "X: " << xpos << "Y: " << ypos << std::endl;
        line = ss.str();
        OutputDebugString(line.c_str());

        if (checkButtonCollision(xpos, ypos, startBtn_))
        {
            switchScreen_ = true;
            screenIndex_ = 1;
        }
        if (checkButtonCollision(xpos, ypos, exitBtn_))
        {
            switchScreen_ = true;
            screenIndex_ = -1;
        }
    }
}

void TitleScreen::render(){
    glBindVertexArray(menuButtonVAOID_);

    startBtn_->render();
    exitBtn_->render();
}

void TitleScreen::update(){}