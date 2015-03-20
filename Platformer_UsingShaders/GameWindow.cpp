#include "GameWindow.h"
#include <fstream>
#include <vector>
#include "GLSLParser.h"

struct VertexData{
    GLfloat positions[4];
};

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
    VertexData quadVertices[] = {
        { -0.5f, 0.5f, 0.0f, 1.0f },  //Left-Top ID: 0
        { -0.5f, -0.5f, 0.0f, 1.0f }, //Left-Bottom ID:1
        { 0.5f, -0.5f, 0.0f, 1.0f },  //Right-Bottom ID:2
        { 0.5f, 0.5f, 0.0f, 1.0f }    //Right-Top ID:3
    };

    //The colors that each vertex will in respective with quadVertices
    VertexData colors[] = {
            { 1.0f, 0.0f, 0.0f, 1.0f },
            { 0.0f, 1.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f, 1.0f },
            { 1.0f, 1.0f, 1.0f, 1.0f }
    };

    //OpenGL expects to draw vertices in counter-clockwise order by default
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
    //Resemble the location of each vertex.
    glGenBuffers(1, &bufferID_);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    //Put the Vertex Buffer Object in the attribute list at index 0
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, positions));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Create a new Vertex Color Object
    glGenBuffers(1, &colorID_);
    glBindBuffer(GL_ARRAY_BUFFER, colorID_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, positions));
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
}

GameWindow::GameWindow(int width, int height, const char* winTitle)
    :vertexID_{ 0 }, bufferID_{ 0 }, colorID_{ 0 }, indicesID_{ 0 }, vsID_{ 0 }, fsID_{ 0 }, pID_{ 0 }{
    setupGL(width, height, winTitle);
    setupQuad();
    setupShaders();
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
    glClear(GL_COLOR_BUFFER_BIT);

    // Use shader program we created
    glUseProgram(pID_);


    //Bind to the Vertex Object Array with information about quad
    glBindVertexArray(vertexID_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //Bind to the Index Vertex Buffer Object, which holds information about the order of the vertices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID_);

    //Draw the vertices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    //Deselect
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void GameWindow::update(){

}