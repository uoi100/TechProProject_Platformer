#define GLFW_INCLUDE_GLU
#include "Prefix.h"
#include "PlayerSprite.h"

class GameWindow
{
private:
    GLfloat width_;
    GLfloat height_;
    GLFWwindow* window_;
    GLuint vertexBufferID_;
    GLuint textureBufferID_;
    std::vector<Sprite*> *renderArray_;

    GLuint loadAndBufferImage(const char* fileName);
    void setupGL(int width, int height, const char* title);
public:
    GLFWwindow* getWindow();    
    GameWindow(GLfloat width, GLfloat height, const char* winTitle);
    ~GameWindow();

    void render();
    void update();
};