#include "Prefix.h"
#include <vector>
#include "Sprite.h"

class GameWindow{
private:
    GLFWwindow* window_;
    int width_, height_;
    const double PI = 3.14159265358979323846;
    float positionX;
    glm::vec3 position = glm::vec3(0, 0, 2);
    float lastTime = 0;

    // Quad variables
    GLuint  vertexID_;
    GLuint  bufferID_;
    GLuint  indicesID_;

    VertexData quadVertices_[4];

    // Shader Variables
    GLuint vsID_;
    GLuint fsID_;
    GLuint pID_;

    // Texture Variables
    std::vector<GLint>  textureID_;

    //Moving Variables
    GLuint projectionMatrixLocation_;
    GLuint viewMatrixLocation_;
    GLuint modelMatrixLocation_;
    glm::mat4x4 *projectionMatrix_;
    glm::mat4x4 *viewMatrix_;
    glm::mat4x4 *modelMatrix_;
    glm::vec3 modelPos_;
    glm::vec3 modelAngle_;
    glm::vec3 modelScale_;
    glm::vec3 cameraPos_;

    //Game Variables
    Sprite *player_;
    Sprite *background_;
    Sprite *overlay_;

    // Functions

    int loadShader(std::string filename, int type);

    // Setup Functions
    void setupShaders();
    void setupQuad();
    void setupTextures();
    void setupDevIL();
    void setupMatrices();
    void setupGL(int width, int height, const char* winTitle);
public:
    GameWindow(int width, int height, const char* winTitle);
    ~GameWindow();

    GLFWwindow* getWindow();
    void render();
    void update();
};