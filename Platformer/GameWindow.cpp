#include "GameWindow.h"
#include <string>

GLFWwindow* GameWindow::getWindow(){
    return window_;
}

GameWindow::GameWindow(GLfloat width, GLfloat height, const char* winTitle):
width_{ width }, height_{ height }{
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window_ = glfwCreateWindow(width_, height_, winTitle, NULL, NULL);
    glViewport(0, 0, width_, height_);

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);

    // Set the current matrix to the GL_PROJECTION matrix
    // Which is the matrix that "Projects" how you see when things are drawn
    glMatrixMode(GL_PROJECTION);  
    // replace the current matrix with the identity matrix
    glLoadIdentity();
    // Defines a 2D orthographic projection matrix
    // basically the clipping plane of how things will be drawn
    gluOrtho2D(0, width_, 0, height_);
    // Set the current matrix to the GL_MODELVIEW matrix
    // Which is basically for our objects to be drawn and then translated onto our projection
    glMatrixMode(GL_MODELVIEW);

}

void GameWindow::render(){
    //glfwGetFramebufferSize(window_, &width, &height);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2d(0.0f, 0.0f);
    glVertex2d(100.0f, 0.0f);
    glVertex2d(100.0f, 100.0f);
    glVertex2d(0.0f, 100.0f);
    glEnd();

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void GameWindow::update(){

}