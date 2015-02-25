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
    GLuint projectileBufferID_;

    PlayerSprite* player_;
    std::vector<Sprite*> *projectileArray_;

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