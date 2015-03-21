#include "GameWindow.h"
#include <fstream>
#include <vector>
#include "GLSLParser.h"

// We want to render load and buffer images for drawing
GLuint loadAndBufferImage(const char* fileName, int textureUnit, int width, int height){

    GLuint textureBufferID = SOIL_load_OGL_texture(
        fileName,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_MIPMAPS);

    if (textureBufferID == 0)
        return NULL;

    // Create a new texture object in memory and bind it
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureBufferID);

    // ALL RGB bytes are aligned to each other and each component is 1 byte
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Upload the texture data and generate mip maps (for scaling)
    //glGenerateMipmap(GL_TEXTURE_2D);

    // Sets Texture Environment, in this case we want to set the environment,
    // to make the image transparent

    // Setup the ST(UV) coordinate system
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Setup what to do when the texture has to be scaled
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ONE_MINUS_SRC_ALPHA);

    return textureBufferID;
}

void GameWindow::setupTextures(){
    textureID_.push_back(loadAndBufferImage("./Image/ash_uvgrid01.jpg", GL_TEXTURE0, 1024, 1024));
    textureID_.push_back(loadAndBufferImage("./Image/ash_uvgrid06.jpg", GL_TEXTURE0, 1024, 1024));
    textureID_.push_back(loadAndBufferImage("./Image/shana.png", GL_TEXTURE0, 750, 1064));
}

int GameWindow::loadShader(std::string filename, int type){
    std::ifstream read(filename);
    std::string line;
    std::string out;
    int shaderID = 0;

    try{
        if (read.is_open()){
            while (getline(read, line)){
                if(!line.empty())
                    out += removeSpaces(line) + '\n';
            }
            read.close();
        }
    }
    catch (std::exception e) {
        OutputDebugString("Error occured while reading file\n");
    }
    shaderID = glCreateShader(type);
    const GLchar* shaderSource = out.c_str();
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);
    
    if(getStatus(shaderID))   
        return shaderID;
    return 0;
}

void GameWindow::setupShaders(){
    int errorCheckValue = glGetError();
    // Load the vertex shader
    vsID_ = loadShader("./vertex.glsl", GL_VERTEX_SHADER);
    // Load the fragment shader
    fsID_ = loadShader("./fragment.glsl", GL_FRAGMENT_SHADER);

    // Create a new shader program that links both shaders
    pID_ = glCreateProgram();
    glAttachShader(pID_, vsID_);
    glAttachShader(pID_, fsID_);

    // Position information will be attribute 0
    glBindAttribLocation(pID_, 0, "in_Position");
    // Color information will be attribute 1
    glBindAttribLocation(pID_, 1, "in_Color");
    // Texture information will be attribute 2
    glBindAttribLocation(pID_, 2, "in_TextureCoord");

    glLinkProgram(pID_);
    glValidateProgram(pID_);

    errorCheckValue = glGetError();
    if (errorCheckValue != GL_NO_ERROR){
        OutputDebugString("Error could not create the shaders");
        exit(EXIT_FAILURE);
    }
}

void GameWindow::setupQuad(){
    //Vertices
    // initialized as such:
    // {position data}, {color data}, {UV-Mapping Data}
    VertexData v0 = { { -1, 1, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0, 0 } }; // Left-Top
    VertexData v1 = { { -1, -1, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 1 } }; // Left-Bottom
    VertexData v2 = { { 1, -1, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1, 1 } }; // Right-Bottom
    VertexData v3 = { { 1, 1, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1, 0 } }; // Right-Top

    VertexData quadVertices[] = { v0, v1, v2, v3 };

    //OpenGL expects to draw vertices in counter-clockwise order by default
    //So we create an array called quads that determine the vertex for us
    //to use to make a square. Note that we need two triangles to make a
    //a square
    byte quads[] = {
        // Left-Bottom Triangle
        0, 1, 2,
        // Right-Top Triangle
        2, 3, 0
    };

    //Create a Vertex Array Object in memory (glGenVertexArrays)
    //Select the newly created Vertex Array Object (glBindVertexArray)
    //Note: By default a Vertex Array Object can contain 16 Vertex Buffer Objects
    glGenVertexArrays(1, &vertexID_);
    glBindVertexArray(vertexID_);

    //Create a new Vertex Buffer Object (glGenBuffers)
    //Select the newly created Vertex Buffer Object (glBindBuffer)
    //A Vertex Buffer Object is a collection of Vectors which in this case
    //Holds the position of the vertex
    //Holds the color information of the vertex
    glGenBuffers(1, &bufferID_);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    //Put the Vertex Buffer Object in the attribute list at index 0
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, positions));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, UVPositions));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Deselect the Vertex Buffer Object and Vertex Array Object
    glBindVertexArray(0);

    //Create a new Vertex Buffer Object for the indices and select it (bind)
    glGenBuffers(1, &indicesID_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID_);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quads), quads, GL_STATIC_DRAW);
    //Deselect the Vertex Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void GameWindow::setupGL(int width, int height, const char* winTitle){
    window_ = glfwCreateWindow(width, height, winTitle, NULL, NULL);

    if (!window_){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_);

    glewExperimental = GL_TRUE;
    if (glewInit())
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
}

GameWindow::GameWindow(int width, int height, const char* winTitle)
    :vertexID_{ 0 }, bufferID_{ 0 }, indicesID_{ 0 }, vsID_{ 0 }, fsID_{ 0 }, pID_{ 0 }{
    setupGL(width, height, winTitle);
    setupQuad();
    setupShaders();
    setupTextures();
}

GameWindow::~GameWindow(){
    // Delete the shaders
    glUseProgram(0);
    glDetachShader(pID_, vsID_);
    glDetachShader(pID_, fsID_);

    glDeleteShader(vsID_);
    glDeleteShader(fsID_);
    glDeleteProgram(pID_);

    //Disable Vertex Object Array Index
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    //Delete Vertex Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &bufferID_);
    glDeleteBuffers(1, &indicesID_);

    //Delete Vertex Array Object
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vertexID_);
}

GLFWwindow* GameWindow::getWindow(){
    return window_;
}

void GameWindow::render(){  
    int textureSelector = 0;

    if (glfwGetKey(window_, GLFW_KEY_1) == GLFW_PRESS)
        textureSelector = 1;
    else if (glfwGetKey(window_, GLFW_KEY_2) == GLFW_PRESS)
        textureSelector = 2;

    glClear(GL_COLOR_BUFFER_BIT);

    // Use shader program we created
    glUseProgram(pID_);

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID_[textureSelector]);


    //Bind to the Vertex Object Array with information about quad
    glBindVertexArray(vertexID_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //Bind to the Index Vertex Buffer Object, which holds information about the order of the vertices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID_);

    glLoadIdentity();

    glTranslatef(200, 200, NULL);
    //Draw the vertices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    //Deselect
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);

    glUseProgram(0);

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void GameWindow::update(){

}