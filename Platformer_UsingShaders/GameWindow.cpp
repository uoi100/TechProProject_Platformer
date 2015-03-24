#include "GameWindow.h"
#include <fstream>
#include <vector>
#include "GLSLParser.h"
#include <cmath>

// We want to render load and buffer images for drawing
GLuint loadAndBufferImage(const char* fileName, int textureUnit, int width, int height){

    ILuint imageID;
    GLuint textureBufferID;

    ilGenImages(1, &imageID);
    ilBindImage(imageID);

    // Load the image based on the file directory given
    if (!ilLoadImage(fileName)){
        std::string error;
        switch (ilGetError()){
        case IL_COULD_NOT_OPEN_FILE: error = "The file pointed to by FileName could not be opened. Either the file does not exist or is in use by another process. \n"; break;
        case IL_ILLEGAL_OPERATION: error = "There is currently no image bound. Use ilGenImages and ilBindImage before calling this function. \n"; break;
        case IL_INVALID_EXTENSION: error = "The file could not be loaded based on extension or header. \n"; break;
        case IL_INVALID_PARAM: error = "FileName was not valid. It was most likely NULL. \n"; break;
        }
        OutputDebugString(error.c_str());
    }

    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

    // Check that the image contains data, if not clean up
    ILubyte *data = ilGetData();
    if (!data){
        ilBindImage(0);
        ilDeleteImages(1, &textureBufferID);
        OutputDebugString("There is no data\n");
        return 0;
    }
    else
        OutputDebugString("There is data\n");

    int const imageWidth = ilGetInteger(IL_IMAGE_WIDTH);
    int const imageHeight = ilGetInteger(IL_IMAGE_HEIGHT);
    int const imageType = ilGetInteger(IL_IMAGE_TYPE);   // matches OpenGL
    int const imageFormat = ilGetInteger(IL_IMAGE_FORMAT); // matches OpenGL


    // Generate a texture name
    glGenTextures(1, &textureBufferID);
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureBufferID);

    //Enable Texture Transparency
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // Set the pixel store parameters
    glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); // rows are tightly packed
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // pixels are tightly packed
    
    // Upload the texture data and generate mip maps (for scaling)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // Setup the ST(UV) coordinate system
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Setup what to do when the texture has to be scaled
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //glGenTextures(1, &textureBufferID);

    if (ilGetError()){
        OutputDebugString("Some Error Occured with DevIL\n");
    }

    return textureBufferID;
}

void GameWindow::setupTextures(){
    textureID_.push_back(loadAndBufferImage("./Image/ash_uvgrid01.jpg", GL_TEXTURE0, 1024, 1024));
    textureID_.push_back(loadAndBufferImage("./Image/transparentGlass.png", GL_TEXTURE0, 750, 1064));
    textureID_.push_back(loadAndBufferImage("./Image/Shana.png", GL_TEXTURE0, 1, 1));
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
    // Texture information will be attribute 1
    glBindAttribLocation(pID_, 1, "in_TextureCoord");

    glLinkProgram(pID_);
    glValidateProgram(pID_);

    errorCheckValue = glGetError();
    if (errorCheckValue != GL_NO_ERROR){
        OutputDebugString("Error could not create the shaders");
        exit(EXIT_FAILURE);
    }
}

void GameWindow::setupQuad(){
    int width = 400;
    int height = 400;
    //Vertices
    // initialized as such:
    // {position data}, {color data}, {UV-Mapping Data}
    VertexData v0 = { { width/2, -height/2, 0.0f }, { 0, 0 } }; // Left-Top
    VertexData v1 = { { width/2, height/2, 0.0f }, { 0, 1 } }; // Left-Bottom
    VertexData v2 = { { -width/2, height/2, 0.0f }, { 1, 1 } }; // Right-Bottom
    VertexData v3 = { { -width/2, -height/2, 0.0f }, { 1, 0 } }; // Right-Top

    quadVertices_[0] = v0;
    quadVertices_[1] = v1;
    quadVertices_[2] = v2;
    quadVertices_[3] = v3;

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices_), quadVertices_, GL_STREAM_DRAW);
    //Put the Vertex Buffer Object in the attribute list at index 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, positions));
    //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData),
    //    (GLvoid *)offsetof(VertexData, color));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData),
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

void GameWindow::setupDevIL(){
    ilInit();
    iluInit();
    ilutInit();
    ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
    ilEnable(IL_ORIGIN_SET);
    ilutRenderer(ILUT_OPENGL);
}

void GameWindow::setupMatrices(){
    glm::mat4 trans;
   
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;

    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
        );

    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        0
    );

    glm::vec3 up = glm::cross(right, direction);

    glm::vec3 moveUp = glm::vec3(
        0,
        sin(verticalAngle - 3.14 / 2.0f),
        0
    );

    // Projection Matrix
    glm::mat4 projection = glm::ortho(0.0f, -(float)width_ , 0.0f, -(float)height_, 0.1f, 100.0f);

    // View Matrix
    glm::mat4 view = glm::lookAt(
        position, // Camera is at (4, 3, 3) in world space
        position+direction, // Looks at the origin
        up
    );


    // Model Matrix: an identity model (model will be at the origin)
    glm::mat4 model = glm::mat4(1.0f);
      
    glm::mat4 MVP = projection * view * model;

    GLuint matrixID = glGetUniformLocation(pID_, "mvp");

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    // for each model you render, since the MVP will be different (atleast the M part)
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(MVP));
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

    glEnable(GL_BLEND); 
}

GameWindow::GameWindow(int width, int height, const char* winTitle)
:width_{ width }, height_{ height }, vertexID_{ 0 }, bufferID_{ 0 }, indicesID_{ 0 }, vsID_{ 0 },
fsID_{ 0 }, pID_{ 0 }, projectionMatrixLocation_{ 0 }, viewMatrixLocation_{ 0 }, modelMatrixLocation_{ 0 }
{
    setupGL(width, height, winTitle);
    setupQuad();
    setupShaders();
    setupDevIL();
    setupTextures();


    //setup game

    player_ = new Sprite(glm::vec2(100, 100), glm::vec2(width_, height_));
    player_->setupShaders(vertexID_, textureID_[2], indicesID_, pID_, quadVertices_);

    background_ = new Sprite(glm::vec2(100, 100), glm::vec2(width_, height_));
    background_->setupShaders(vertexID_, textureID_[0], indicesID_, pID_, quadVertices_);
    background_->setPosition(glm::vec2(width_ / 2, height_ / 2));

    overlay_ = new Sprite(glm::vec2(100, 100), glm::vec2(width_, height_));
    overlay_->setupShaders(vertexID_, textureID_[1], indicesID_, pID_, quadVertices_);
    overlay_->setPosition(glm::vec2(width_ / 2, height_ / 2));
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

    //Clear buffer to preset colors
    glClear(GL_COLOR_BUFFER_BIT);

    // Enable Alpha-Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Use shader program we created
    glUseProgram(pID_);

    // Background
    background_->render();
    // Entities
    player_->render();
    // Overlays
    overlay_->render();

    // Deselect the Program
    glUseProgram(0);

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void GameWindow::update(){

    player_->update();

}