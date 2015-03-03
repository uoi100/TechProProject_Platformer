#include "GameWindow.h"

GameWindow::GameWindow(int width, int height, const char* winTitle){
    window_ = glfwCreateWindow(width, height, winTitle, NULL, NULL);

    if (!window_){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_);
}

GLFWwindow* GameWindow::getWindow(){
    return window_;
}

void GameWindow::render(){
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void GameWindow::update(){

}