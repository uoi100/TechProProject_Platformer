#include "GameWindow.h"
#include <string>

struct VertexData{
    GLfloat positionCoordinates[3];
    GLfloat textureCoordinates[2];
};

// VertexData of a 80x120 Square
VertexData vertices[] = {
        {{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }},     // Bottom-Left
        {{ 80.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }},   // Bottom-Right
        {{ 80.0f, 120.0f, 0.0f }, { 1.0f, 1.0f }}, // Top-Right
        {{ 0.0f, 120.0f, 0.0f }, { 0.0f, 1.0f }}    // Top-Left
};

GLFWwindow* GameWindow::getWindow(){
    return window_;
}

// We want to render load and buffer images for drawing
GLuint GameWindow::loadAndBufferImage(const char* fileName){

    GLuint textureBufferID = SOIL_load_OGL_texture(
        fileName,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA);

    if (textureBufferID == 0)
        return NULL;

    glBindTexture(GL_TEXTURE_2D, textureBufferID);

    // Sets Texture Environment, in this case we want to set the environment
    // to make the image transparent
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ONE_MINUS_SRC_ALPHA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return textureBufferID;
}

// Constructor
// Description: Creates the window and sets the openGL drawing context to that window.
// This is where the basic initialization goes, such as how the window is drawn,
// what available drawing functions that will be used, how objects will be drawn on the screen, etc etc.
GameWindow::GameWindow(GLfloat width, GLfloat height, const char* winTitle):
width_{ width }, height_{ height }, vertexBufferID_{ 0 }, textureBufferID_{ 0 }{
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window_ = glfwCreateWindow(width_, height_, winTitle, NULL, NULL);

    if (!window_)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_);

    //Glew Init must be initialized after a Context is set.
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    //Specifies the area that will be drawn
    glViewport(0, 0, width_, height_);
    // Clear background and fill with the color white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Enable usage of 2D Textures
    glEnable(GL_TEXTURE_2D);
    // Enable usage of Alpha Blending, for transparent images
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // For Double-Buffering we want to be able to switch windows at a constant interval
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

    // Lets the drawing know the texture coordinates of the array, this is used so it knows the corners of the image
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, textureCoordinates));

    textureBufferID_ = loadAndBufferImage("./Image/test.png");
    // Assignment the image id to the Sprite
    player_ = new Sprite(textureBufferID_);
}

/*
 * Description: Main drawing operations will be here.
 */
void GameWindow::render(){
    //glfwGetFramebufferSize(window_, &width, &height);

    glClear(GL_COLOR_BUFFER_BIT);

    player_->render();

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void GameWindow::update(){

}