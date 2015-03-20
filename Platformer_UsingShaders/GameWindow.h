#include "Prefix.h"

class GameWindow{
private:
    GLFWwindow* window_;

    GLuint vertexID_;
    GLuint bufferID_;
    GLuint indicesID_;
    GLuint colorID_;
    
    // Vertex Shader ID
    GLuint vsID_;
    // Fragment Shader ID
    GLuint fsID_;
    // Program ID
    GLuint pID_;

    int loadShader(std::string filename, int type);
    void setupShaders();
    void setupQuad();
    void setupGL(int width, int height, const char* winTitle);
public:
    GameWindow(int width, int height, const char* winTitle);
    ~GameWindow();

    GLFWwindow* getWindow();
    void render();
    void update();
};