#include "Prefix.h"

class GameWindow{
private:
    GLFWwindow* window_;

    GLuint vertexID_;
    GLuint bufferID_;

    void setupQuad();
    void setupGL(int width, int height, const char* winTitle);
public:
    GameWindow(int width, int height, const char* winTitle);
    ~GameWindow();

    GLFWwindow* getWindow();
    void render();
    void update();
};