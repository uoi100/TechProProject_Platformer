#include <GLFW\glfw3.h>

#include <stdlib.h>
#include <stdio.h>

void error_callback(int error, const char* description);
static void keyInput_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(){
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(640, 480, "Platformer", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, keyInput_callback);   

    while (!glfwWindowShouldClose(window))
    {
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        glBegin(GL_QUADS);
        glVertex2d(-0.5f, -0.5f);
        glVertex2d(0.5f, -0.5f);
        glVertex2d(0.5f, 0.5f);
        glVertex2d(-0.5f, 0.5f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

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