#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

class GameWindow
{
private:
    GLfloat width_;
    GLfloat height_;
    GLFWwindow* window_;
public:
    GLFWwindow* getWindow();

    GameWindow(GLfloat width, GLfloat height, const char* winTitle);

    void render();
    void update();
};