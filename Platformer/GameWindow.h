#define GLFW_INCLUDE_GLU
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

class GameWindow
{
private:
    GLfloat width_;
    GLfloat height_;
    GLFWwindow* window_;
    GLuint vertexBufferID_;
    GLuint textureBufferID_;
    GLuint loadAndBufferImage(const char* fileName);
public:
    GLFWwindow* getWindow();

    GameWindow(GLfloat width, GLfloat height, const char* winTitle);

    void render();
    void update();
};