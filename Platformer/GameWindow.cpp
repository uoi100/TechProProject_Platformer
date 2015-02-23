#include "GameWindow.h"
#include <string>

struct VertexData{
    GLfloat positionCoordinates[3];
};

// VertexData of a 100x100 Square
VertexData vertices[] = {
        { 0.0f, 0.0f, 0.0f },
        { 100.0f, 0.0f, 0.0f },
        { 100.0f, 100.0f, 0.0f },
        { 0.0f, 100.0f, 0.0f } };

GLFWwindow* GameWindow::getWindow(){
    return window_;
}

GameWindow::GameWindow(GLfloat width, GLfloat height, const char* winTitle):
width_{ width }, height_{ height }, vertexBufferID_{ 0 }{
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window_ = glfwCreateWindow(width_, height_, winTitle, NULL, NULL);

    if (!window_)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //Specifies the area that will be drawn
    glViewport(0, 0, width_, height_);

    glfwMakeContextCurrent(window_);

    //Glew Init must be initialized after a Context is set.
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    glfwSwapInterval(1);

    // Set the current matrix to the GL_PROJECTION matrix
    // Which is the matrix that "Projects" how you see when things are drawn
    glMatrixMode(GL_PROJECTION);  
    // replace the current matrix with the identity matrix
    glLoadIdentity();
    // Defines a 2D orthographic projection matrix
    // basically the clipping plane which "clips out" things that would be
    // drawn outside as we would not see it anyways.
    gluOrtho2D(0, width_, 0, height_);
    // Set the current matrix to the GL_MODELVIEW matrix
    // Which is basically for our objects to be drawn and then translated onto our projection
    glMatrixMode(GL_MODELVIEW);

    // Create a name buffer object for vertexBufferID
    glGenBuffers(1, &vertexBufferID_);
    // Sets an array buffer pointed at vertexBufferID
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID_);
    // Adds the data of vertices into the buffer for static drawing operations
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Allows the client to use vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    
    // Lets the drawing know the size of the array, what data type it should expect,
    // the size of the struct, and an offset of the struct and the member that will be read.
    glVertexPointer(3, GL_FLOAT, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, positionCoordinates));
    

}

/*
 * Description: Main drawing operations will be here.
 */
void GameWindow::render(){
    //glfwGetFramebufferSize(window_, &width, &height);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0.0f, 0.0f, 1.0f);

    glDrawArrays(GL_QUADS, 0, 4);

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void GameWindow::update(){

}