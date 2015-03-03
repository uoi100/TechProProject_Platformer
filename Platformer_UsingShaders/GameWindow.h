#include "Prefix.h"

class GameWindow{
private:
    GLFWwindow* window_;
public:
    GameWindow(int width, int height, const char* winTitle);

    GLFWwindow* getWindow();
    void render();
    void update();
};