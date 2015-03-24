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

    // Setup functions
    void setupGL(int width, int height, const char* title);
    void setupDevIL();
public: 
    // Constructor / Deconstructor Functions
    GameWindow(int width, int height, const char* winTitle);
    ~GameWindow();

    // Getter Functions
    int getWidth();
    int getHeight();
    GLFWwindow* getWindow();

    // Game Window Functions that we expect to use in main
    void mouseEvent(int button, int action);
    void render();
    void update();
};



