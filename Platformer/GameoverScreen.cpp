#include "GameoverScreen.h"

/*
* @Author Calvin Truong Wesley Dale
* @Version 1.0
* @Description
* The gameover screen when the player loses all of his/her lives
*/
bool GameoverScreen::checkButtonCollision(int xpos, int ypos, Sprite* btn){
    return (xpos >= btn->getPosition().x - btn->getWidth() / 2 &&
        xpos <= btn->getPosition().x + btn->getWidth() / 2 &&
        ypos >= btn->getPosition().y - btn->getHeight() / 2 &&
        ypos <= btn->getPosition().y + btn->getHeight() / 2);
}

GameoverScreen::GameoverScreen(int width, int height): Screen(width, height){
    glm::vec2 buttonSize(300, 100);

    // Create Button Vertex
    createVertex(&menuButtonVertexID_, &menuButtonBufferID_, &menuButtonIndices_, buttonSize.x, buttonSize.y);

    // Create Button Textures
    backToTitleID_ = loadAndBufferImage("./Image/Title.png", GL_TEXTURE0);
    gameOverID_ = loadAndBufferImage("./Image/Gameover.png", GL_TEXTURE0);

    // Create Buttons
    titleBtn_ = new Sprite(backToTitleID_, glm::vec2(winSize_.x / 2, winSize_.y / 2), buttonSize, winSize_);

    // Create Labels
    gameOverLabel_ = new Sprite(gameOverID_, glm::vec2(winSize_.x / 2, winSize_.y / 2 + buttonSize.y * 2), buttonSize, winSize_);
}

GameoverScreen::~GameoverScreen(){
    // Delete Button Vertex Data
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &menuButtonIndices_);
    glDeleteBuffers(1, &menuButtonBufferID_);
    glDeleteVertexArrays(1, &menuButtonVertexID_);

    // Delete Button Textures
    glDeleteTextures(1, &backToTitleID_);
    glDeleteTextures(1, &gameOverID_);

    // Delete the Sprites
    delete titleBtn_;
    delete gameOverLabel_;
}

void GameoverScreen::mouseEvent(int button, int action){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);
        ypos = winSize_.y - ypos;

        if (checkButtonCollision(xpos, ypos, titleBtn_)){
            switchScreen_ = true;
            screenIndex_ = 0;
        }
    }
}

void GameoverScreen::render(){
    // Select the menu button vertex
    glBindVertexArray(menuButtonVertexID_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, menuButtonIndices_);

    // Render our buttons
    titleBtn_->render();

    // Render our labels
    gameOverLabel_->render();

    // Deselect
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
