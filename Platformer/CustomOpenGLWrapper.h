#include "Prefix.h"
#include <iostream>

// Create Vertex Array Object
void createVertex(GLuint *vertexID, GLuint *bufferID, GLuint *indicesID, int width, int height);

// Load and Buffer Images for rendering
GLuint loadAndBufferImage(const char* fileName, int textureUnit);