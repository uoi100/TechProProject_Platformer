#define GLFW_INCLUDE_GLU
#include "Prefix.h"
#include "PlayerSprite.h"

class GameWindow
{
private:
    int width_;
    int height_;
    GLFWwindow* window_;
    GLuint vertexBufferID_;
    GLuint textureBufferID_;
    std::vector<Sprite*> *renderArray_;

    GLuint loadAndBufferImage(const char* fileName);
    void setupGL(int width, int height, const char* title);
public:
    GLFWwindow* getWindow();    
    GameWindow(int width, int height, const char* winTitle);
    ~GameWindow();

    void mouseEvent(int button, int action);
    int getWidth();
    int getHeight();

    void render();
    void update();
};