#include "GLSLFunctions.h"
#include <fstream>

/*
 *@Description: Initialize a specific type of shader for rendering,
     we use a file for the shader to compile and know how it should be
     rendering the graphics.
 *@filename - The file to be parsed
 *@type - The type of shader to initialize this could be a Vertex or Fragment Shader
 *@Returns GLuint - the shader ID of our specific shader.
 */
GLuint loadShader(std::string filename, int type){
    std::ifstream read(filename);
    std::string line;
    std::string out;

    // Attempt to open the file and read it
    try{
        if (read.is_open()){
            // Read line by line
            while (getline(read, line)){
                if (!line.empty())
                    out += removeSpaces(line) + '\n'; // Remove leading and trailing spaces
            }
        }
        read.close();
    }
    catch (std::exception e) {
        OutputDebugString("Error occured while reading file\n");
        exit(EXIT_FAILURE);
    }

    // Create our shader which could be a Vertex or Fragment Shader
    GLuint shaderID = glCreateShader(type);

    // Get a pointer to our parsed file and store it inside our shader
    const GLchar* shaderSource = out.c_str();
    glShaderSource(shaderID, 1, &shaderSource, NULL);

    // Attempt to compile the parsed file
    glCompileShader(shaderID);

    // Check if the shader successfully compiled
    if (!getStatus(shaderID))
        shaderID = 0;

    // Returns our shaderID which contains a pointer to our shader
    return shaderID;
}

/*
 *@Description: Create our Vertex and Fragment Shaders
    next we create our program and link those shaders to our program.
    We tell our program that our vertex attribute 0 contains the
    vertex position and our vertex attribute 1 will contain
    the texture coordinates.
 *@programID - Our program that controls the vertex and fragment shaders
 *@vertexShaderID - Our Vertex Shader
 *@fragmentShaderID - Our Fragment Shader
 */
void setupShaders(GLuint *programID, GLuint *vertexShaderID, GLuint *fragmentShaderID){
    // Load the vertex shader
    *vertexShaderID = loadShader("./vertex.glsl", GL_VERTEX_SHADER);
    *fragmentShaderID = loadShader("./fragment.glsl", GL_FRAGMENT_SHADER);

    // Create our shader program
    *programID = glCreateProgram();

    // Link the Vertex and Fragment Shaders to our program
    glAttachShader(*programID, *vertexShaderID);
    glAttachShader(*programID, *fragmentShaderID);

    // We tell our program the Attribute 0 of our Vertex which is
    // the vertex position and coordinates will go into the
    // "in_Position" variable in our vertex shader file.
    glBindAttribLocation(*programID, 0, "in_Position");
    
    // Next we tell our program that Attribute 1 of our Vertex which is the
    // texture coordinates will go into the "in_TextureCoord" variable
    // in our Vertex Shader File
    glBindAttribLocation(*programID, 1, "in_TextureCoord");

    // Link our program to OpenGL
    glLinkProgram(*programID);

    // Validate that our program linked correctly
    glValidateProgram(*programID);

    int errorCheckValue = glGetError();
    if (errorCheckValue != GL_NO_ERROR){
        OutputDebugString("Error could not create the shaders");
        exit(EXIT_FAILURE);
    }
}

/*
 *@Description: Removes leading and trailing whitespace
 *@string - The string to remove the leading and trailing white spaces
 *@returns string - The string without leading and trailing white spaces
 */
std::string removeSpaces(std::string string){
    std::string newString;

    // Check from the front to back for leading whitespaces
    for (int i = 0; i < string.length(); i++){
        if (!isspace(string[i])){
            newString = string.substr(i, string.length());
            break;
        }
    }

    // Assignment our string with the leading whitespaces now removed
    string = newString;

    // Check from the back to front for trailing whitespaces
    for (int i = string.length(); i >= 0; i--){
        if (!isspace(string[i])){
            newString = string.substr(0, i);
            break;
        }
    }

    return newString;
}

/*
 *@Description: Checks if the shader was compiled successfully
 *@shaderID - the shader ID to check
 *@returns bool - A boolean that returns true if our shader compiled successfully
 */
bool getStatus(GLuint shaderID){
    // Get the status to see if our shader compiled
    GLint isCompiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);

    // Get the length of the information log which includes the NULL character
    GLint maxLength = 0;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

    // Get the information log
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

    // Create a string stream to store the characters
    std::stringstream ss;

    // Store the characters into the string stream
    for (GLchar key : errorLog)
        ss << key;

    // insert a new line character
    ss << '\n';

    // Print the information log stored in the string stream
    OutputDebugString(ss.str().c_str());

    // if the compile failed then delete the shader and return false
    if (isCompiled == GL_FALSE){
        glDeleteShader(shaderID); // Delete the shader to avoid memory leaks
        return false;
    }

    return true;
}