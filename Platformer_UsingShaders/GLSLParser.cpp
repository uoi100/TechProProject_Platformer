#include "GLSLParser.h"
#include <vector>

std::string removeSpaces(std::string string){
    std::string newString;

    for (int i = 0; i < string.length(); i++){
        if (!isspace(string[i])){
            newString = string.substr(i, string.length());
            break;
        }
    }

    string = newString;
    for (int i = string.length(); i >= 0; i--){
        if (!isspace(string[i])){
            newString = string.substr(0, i);
            break;
        }
    }

    return newString;
}

bool getStatus(GLuint shaderID){
    GLint isCompiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
    
    GLint maxLength = 0;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

    std::stringstream ss;

    for (GLchar key : errorLog)
        ss << key;

    ss << '\n';

    OutputDebugString(ss.str().c_str());

    if (isCompiled == GL_FALSE){
        glDeleteShader(shaderID); // Delete the shader to avoid memory leaks
        return false;
    }

    return true;
}