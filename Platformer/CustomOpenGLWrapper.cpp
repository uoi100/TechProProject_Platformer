#include "CustomOpenGLWrapper.h"

void createVertexBuffer(GLuint *objectID, GLuint *bufferID, int width, int height){
    glGenVertexArrays(1, objectID);
    glBindVertexArray(*objectID);
    // Create a name buffer object for vertexBufferID
    glGenBuffers(1, bufferID);
    // Sets an array buffer pointed at vertexBufferID
    glBindBuffer(GL_ARRAY_BUFFER, *bufferID);
    // Create a vertex with 4 points for our entities
    VertexData square[] = {
        { { -width / 2, -height / 2, 0.0f }, { 0.0f, 0.0f } },     // Bottom-Left
        { { width / 2, -height / 2, 0.0f }, { 1.0f, 0.0f } },   // Bottom-Right
        { { width / 2, height / 2, 0.0f }, { 1.0f, 1.0f } }, // Top-Right
        { { -width / 2, height / 2, 0.0f }, { 0.0f, 1.0f } }    // Top-Left
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, positionCoordinates));

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

// We want to render load and buffer images for drawing
GLuint loadAndBufferImage(const char* fileName){

    GLuint textureBufferID = SOIL_load_OGL_texture(
        fileName,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_NTSC_SAFE_RGB);

    if (textureBufferID == 0)
        return NULL;

    glBindTexture(GL_TEXTURE_2D, textureBufferID);

    // Sets Texture Environment, in this case we want to set the environment
    // to make the image transparent
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ONE_MINUS_SRC_ALPHA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return textureBufferID;
}