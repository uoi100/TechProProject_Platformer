#include <Windows.h>
#include <GLFW\glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "GameWindow.h"

void error_callback(int error, const char* description);
static void keyInput_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow ){

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    GameWindow window(800*16/9, 800, "PlatformerGame");

    if (!window.getWindow())
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window.getWindow(), keyInput_callback);   

    while (!glfwWindowShouldClose(window.getWindow()))
    {
        window.render();
    }

    glfwDestroyWindow(window.getWindow());

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

/*
 * Description: Error handling callback, if something happens then the glfw libary will call the callback function.
 */
void error_callback(int error, const char* description){
    fputs(description, stderr);
}

/*
 * Description: When a key is pressed, the callback function is executed to handle the event.
 * @GLFWwindow* window - The currently focused window that the key was pressed on
 * @int key - The value of the key that was triggered
 * @int scancode - I don't know what this does yet
 * @int action - The action of the key which could be pressed or released
 * @int mods - I don't know what this does yet
 */
static void keyInput_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // If the ESCAPE key is pressed, do this.
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}