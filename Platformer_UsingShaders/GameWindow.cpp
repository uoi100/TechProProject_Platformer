#include "GameWindow.h"

struct VertexData{
    GLfloat positions[3];
};

void GameWindow::setupQuad(){
    //Vertices
    VertexData quadVertices[] = {
        { -0.5f, 0.5f, 0.0f },  //Left-Top ID: 0
        { -0.5f, -0.5f, 0.0f }, //Left-Bottom ID:1
        { 0.5f, -0.5f, 0.0f },  //Right-Bottom ID:2
        { 0.5f, 0.5f, 0.0f }    //Right-Top ID:3
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, positions));

    //Deselect the Vertex Buffer Object and Vertex Array Object
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

    if (glewInit())
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, width, height);
}

GameWindow::GameWindow(int width, int height, const char* winTitle)
    :vertexID_{ 0 }, bufferID_{ 0 }{
    setupGL(width, height, winTitle);
    setupQuad();
}

GameWindow::~GameWindow(){
    //Disable Vertex Object Array Index
    glDisableVertexAttribArray(0);

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

    //Bind to the Vertex Object Array with information about quad
    glBindVertexArray(vertexID_);
    glEnableVertexAttribArray(0);

    //Bind to the Index Vertex Buffer Object, which holds information about the order of the vertices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID_);

    //Draw the vertices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    //Deselect
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void GameWindow::update(){

}