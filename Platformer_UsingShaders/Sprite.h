#include "Prefix.h"

class Sprite{
private:

    // Shader Variables
    GLuint textureID_;
    GLuint vertexID_;
    GLuint indicesID_;
    GLuint programID_;
    VertexData vertices_[4];

    // Size Variables
    glm::vec2 size_;
    glm::vec2 winSize_;

    // Game Variables
    glm::vec3 position_;
    GLfloat speed_;
    int windowWidth_;
    int windowHeight_;

    // Matrix Transformation Function
    void matrixTransformation();

    // Game Functions
    void checkButtons();

public:
    Sprite(glm::vec2 size, glm::vec2 winSize);

    virtual void setupShaders(GLuint vertexID, GLuint textureID, GLuint indicesID, GLuint programID, VertexData vertices[4]);
    virtual void setPosition(glm::vec2 position);

    virtual void render();
    virtual void update();
};