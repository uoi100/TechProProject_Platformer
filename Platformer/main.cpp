#include <Windows.h>

#include <stdlib.h>
#include <stdio.h>

#include "GameWindow.h"

#define Updates_Per_Second 60

GameWindow* gameWindow;

void error_callback(int error, const char* description);
static void keyInput_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


void mouseEvent(GLFWwindow* window, int button, int action, int mods){
    gameWindow->mouseEvent(button, action);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow ){
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    gameWindow = new GameWindow(800, 600, "PlatformerGame");

    glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouseEvent);

    if (!gameWindow->getWindow())
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // For Double-Buffering we want to be able to switch windows at a constant interval
    glfwSwapInterval(0);
    
    double lastTime = glfwGetTime();
    double deltaTime = 0.0f;

    while (!glfwWindowShouldClose(gameWindow->getWindow()))
    {
        gameWindow->render();

        deltaTime += (glfwGetTime() - lastTime) * Updates_Per_Second;
        lastTime = glfwGetTime();
        while (deltaTime >= 1.0f){
            gameWindow->update();
            --deltaTime;
        }
    }

    glfwDestroyWindow(gameWindow->getWindow());
    delete gameWindow;

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

/*
 * Description: Error handling callback, if something happens then the glfw libary will call the callback function.
 */
void error_callback(int error, const char* description){
    fputs(description, stderr);
}