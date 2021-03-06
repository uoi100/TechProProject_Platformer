#include "GameWindow.h"
#include <algorithm>
#include <string>
#include "GLSLFunctions.h"

/*
 *@Author Calvin Truong and Wesley Dale
 *@Version 2.0
 *@Description: The main window context that will be rendered on
    The game window contains different screens such as the title screen
    and game screen and determines which screen will be drawn
    on the window context.
 */

// Sets up OpenGL and Glew which allows for the graphics operations to work.
/*
 *@Description: Initialize openGL using glfw(openGL & win32 wrapper) which creates the window context for graphic functions to draw on,
    as well as initialize glew (openGL extensible wrangler) which is responsible for extending the drawing capabilities of openGL
 *
 *@width - The width of the window that will be used to draw on
 *@height - The height of the window that will be used to draw on
 *@title - The window title that is displayed on the top of the window.
 */
void GameWindow::setupGL(int width, int height, const char* title){
    // this function makes it so that the user does not accidentally drag the window
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // create the window by the width and height, give it a title, the 4th parameter is set to NULL
    // to let the function know that the context is not going to be full-screen.
    window_ = glfwCreateWindow(width, height, title, NULL, NULL);

    // If the function had failed to create the window context then terminate the program.
    if (!window_)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Store the window context as the current context
    glfwMakeContextCurrent(window_);

    // After the current context is set, initialize glew
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    // if glew fails to initalize then terminate the program.
    if (err != GLEW_OK){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //Enable Blending which is used to render textures
    //and "blend" textures such as ones with transparency so that
    //the textures render properly with the window context.
    glEnable(GL_BLEND);
}

/*
 *@Description: Sets up Development Image Libary (DevIL)
 * This library is responsible for reading the byte data of images
   for OpenGL to render
 */
void GameWindow::setupDevIL(){
    ilInit();
    iluInit();
    ilutInit();
    ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
    ilEnable(IL_ORIGIN_SET);
    ilutRenderer(ILUT_OPENGL);
}

/*
 *@Description: Constructor
    - Sets up openGL and Glew
    - Sets up our shaders for rendering
    - Sets up the TitleScreen that the user will load into first.
 *@width - the width of the window context that will be drawn on
 *@height - the height of the window context that will be drawn on
 *@winTitle - the title of the window context that will be drawn on
 */
GameWindow::GameWindow(int width, int height, const char* winTitle):
width_{ width }, height_{ height }{
    //setup OpenGL and Glew
    setupGL(width_, height_, winTitle);

    //setup our shaders
    programID_ = 0;
    vertexShaderID_ = 0;
    fragmentShaderID_ = 0;
    setupShaders(&programID_, &vertexShaderID_, &fragmentShaderID_);

    //setup our Development Image Library (DevIL)
    setupDevIL();

    currentScreen = new TitleScreen(width_, height_);
}

/*
 *@Description: Destructor
    Responsible for cleaning up memory after we're done using them
 */
GameWindow::~GameWindow(){

    // Delete Shader Pointers
    glUseProgram(0);
    glDetachShader(programID_, vertexShaderID_);
    glDetachShader(programID_, fragmentShaderID_);

    glDeleteShader(vertexShaderID_);
    glDeleteShader(fragmentShaderID_);
    glDeleteProgram(programID_);

    // Delete our Screen Pointer
    delete currentScreen;
}

/*
 *@Description: Returns the width of the window context
 *@Returns int - the width of the window context.
 */
int GameWindow::getWidth(){
    return width_;
}

/*
 *@Description: Returns the height of the window context
 *@Returns int - the height of the window context
 */
int GameWindow::getHeight(){
    return height_;
}

/*
 *@Description: Returns the window context
 *@Returns GLFWwindow* - pointer to the window context
 */
GLFWwindow* GameWindow::getWindow(){
    return window_;
}

/*
*@Description: When the mouse is clicked, do the following:
-Left Click: Shoot a projectile at the position of the player and store it
in an array to keep track of.
*@button - The button that was used with the mouse
*@action - The action that that button was doing
*/
void GameWindow::mouseEvent(int button, int action){
    currentScreen->mouseEvent(button, action);
}

/*
 *@Description: The main function that calls the render function
 of the current screen to display onto the window context
 */
void GameWindow::render(){
    // Clear buffer to preset colors
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Use the shader program we created in the constructor
    glUseProgram(programID_);

    // Render our Screen
    currentScreen->render();

    // Deselect our program
    glUseProgram(0);

    // Tell OpenGL that we are finished drawing and are ready to swap the buffers

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

/*
 *@Description: The update function that calls the update function
 of the current screen to update variables that may be required before
 rendering onto the window context
 * The follow indices will call their respective screens:
 * 0 -  The Title Screen
 * 1 -  The Game Screen
 * 2 -  The Gameover Screen
 * 3 -  The Congratulations Screen
 * -1 - Exit the Game
 */
void GameWindow::update(){

    currentScreen->update();

    // Check if the current Screen wants to change to the next screen
    // If it does then get the screen index (hardcoded) of the screen
    // it wants to change to, in this case 1 = the game screen
    if (currentScreen->switchScreen()){
        if (currentScreen->screenIndex() == 0){
            Screen *old = currentScreen;
            currentScreen = new TitleScreen(width_, height_);
            delete old;
        }
        else if (currentScreen->screenIndex() == 1){
            Screen *old = currentScreen;
            currentScreen = new GameScreen(width_, height_);
            delete old;
        }
        else if (currentScreen->screenIndex() == -1){
            glfwSetWindowShouldClose(window_, GL_TRUE);
        }
    }

}