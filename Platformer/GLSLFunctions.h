#ifndef GLSLFUNCTIONS_H
#define GLSLFUNCTIONS_H
#include "Prefix.h"

// Load our shaders
GLuint loadShader(std::string filename, int type);

// Setup Shaders to be used for rendering
void setupShaders(GLuint *programID, GLuint *vertexShaderID, GLuint *fragmentShaderID);

// Removes leading and trailing whitespaces
std::string removeSpaces(std::string string);

// Check if our shaders compiled successfully
bool getStatus(GLuint shaderID);
#endif