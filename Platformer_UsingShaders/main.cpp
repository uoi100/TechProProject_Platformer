#include "Prefix.h"
#include "GameWindow.h"

#define UPDATES_PER_SECOND 60

void callbackError(int error, const char* description);

GameWindow* window;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR pCmdLine, int nCmdShow){
    glfwSetErrorCallback(callbackError);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    window = new GameWindow(600, 480, "Platformer with Shaders");

    if (!window->getWindow())
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(0);

    double lastTime = glfwGetTime();
    double deltaTime = 0.0f;
    while (!glfwWindowShouldClose(window->getWindow())){
        window->render();
        
        deltaTime += (glfwGetTime() - lastTime) * UPDATES_PER_SECOND;
        lastTime = glfwGetTime();
        while (deltaTime >= 1.0f)
        {
            window->update();
            deltaTime--;
        }
    }

    glfwTerminate();
}

void callbackError(int error, const char* description){
    OutputDebugString(description);
}