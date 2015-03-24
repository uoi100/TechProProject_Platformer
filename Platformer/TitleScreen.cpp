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
    const int btnWidth = 300;
    const int btnHeight = 100;
    createVertex(&menuButtonVertexID_, &menuButtonBufferID_, &menuButtonIndices_, btnWidth, btnHeight);

    startBtnID_ = loadAndBufferImage("./Image/Start.png", GL_TEXTURE0);
    exitBtnID_ = loadAndBufferImage("./Image/Exit.png", GL_TEXTURE0);

    startBtn_ = new Sprite(startBtnID_,
        glm::vec2(winSize_.x/2, winSize_.y/2), glm::vec2( btnWidth, btnHeight),
        glm::vec2(winSize_.x, winSize_.y)
    );

    exitBtn_ = new Sprite(exitBtnID_,
        glm::vec2(winSize_.x / 2, winSize_.y / 2 - btnHeight*2), glm::vec2(btnWidth, btnHeight),
        glm::vec2(winSize_.x, winSize_.y)
    );
}

TitleScreen::~TitleScreen(){

    // Delete Button Vertex Data
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &menuButtonIndices_);
    glDeleteBuffers(1, &menuButtonBufferID_);
    glDeleteVertexArrays(1, &menuButtonVertexID_);

    // Delete Button Textures
    glDeleteTextures(1, &startBtnID_);
    glDeleteTextures(1, &exitBtnID_);

    // Delete the Sprites
    delete startBtn_;
    delete exitBtn_;
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
        ypos = winSize_.y - ypos;

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
    // Select the Menu Button Vertex Object Array
    glBindVertexArray(menuButtonVertexID_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, menuButtonIndices_);

    // Render our Buttons
    startBtn_->render();
    exitBtn_->render();

    // Deselect
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void TitleScreen::update(){}