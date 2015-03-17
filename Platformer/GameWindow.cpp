#include "GameWindow.h"
#include <algorithm>
#include <string>

// Sets up OpenGL and Glew which allows for the graphics operations to work.
void GameWindow::setupGL(int width, int height, const char* title){    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window_ = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window_)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_);

    //Glew Init must be initialized after a Context is set.
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    //Specifies the area that will be drawn
    glViewport(0, 0, width_, height_);
    // Clear background and fill with the color white
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Enable usage of 2D Textures
    glEnable(GL_TEXTURE_2D);
    // Enable usage of Alpha Blending, for transparent images
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set the current matrix to the GL_PROJECTION matrix
    // Which is the matrix that "Projects" how you see when things are drawn
    glMatrixMode(GL_PROJECTION);
    // replace the current matrix with the identity matrix
    glLoadIdentity();
    // Defines a 2D orthographic projection matrix
    // basically the clipping plane which "clips out" things that would be
    // drawn outside as we would not see it anyways.
    gluOrtho2D(0, width_, 0, height_);
    // Set the current matrix to the GL_MODELVIEW matrix
    // Which is basically for our objects to be drawn and then translated onto our projection
    glMatrixMode(GL_MODELVIEW);

    // Allows the client to use vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

/*
 * Description: Constructor
 * - Sets up openGL and Glew
 * - Sets up the Sprites (Entities) for the game.
 */
GameWindow::GameWindow(int width, int height, const char* winTitle):
width_{ width }, height_{ height }, vertexBufferID_{ 0 }, textureBufferID_{ 0 }{
    setupGL(width_, height_, winTitle);

    currentScreen = new GameScreen(width_, height_);
}

GameWindow::~GameWindow(){
    delete currentScreen;
}

/*
 * Description: When the mouse is clicked, do the following:
 * Left Click - Shoot a projectile at the position of the player and store it
 * in an array to keep track of.
 */
void GameWindow::mouseEvent(int button, int action){
    currentScreen->mouseEvent(button, action);
}

int GameWindow::getWidth(){
    return width_;
}

int GameWindow::getHeight(){
    return height_;
}

GLFWwindow* GameWindow::getWindow(){
    return window_;
}


/*
 * Description: Main drawing operations for objects will be here.
 */
void GameWindow::render(){
    glClear(GL_COLOR_BUFFER_BIT);

    currentScreen->render();

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

// This is where the update functions of objects go
void GameWindow::update(){

    currentScreen->update();

}