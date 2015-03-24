#include "Prefix.h"
#include "GameScreen.h"
#include "TitleScreen.h"

class GameWindow
{
private:
    // Window Context Variables
    int width_;
    int height_;
    GLFWwindow* window_;

    // Shader Variables
    GLuint programID_;
    GLuint vertexShaderID_;
    GLuint fragmentShaderID_;

    // Screen Variables
    Screen *currentScreen;

    void setupGL(int width, int height, const char* title);
    void setupDevIL();
public: 
    GameWindow(int width, int height, const char* winTitle);
    ~GameWindow();

    void mouseEvent(int button, int action);
    int getWidth();
    int getHeight();
    GLFWwindow* getWindow();

    void render();
    void update();
};



