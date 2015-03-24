#include "CustomOpenGLWrapper.h"
#include <fstream>

/*
 *@Description: Creates a Vertex Array Object (VAO) that will be stored into the
    Graphics Processing Unit (GPU). The Vertex Array Object also contains an Vertex
    Buffer Object (VBO) which holds the world-Coordinates of where the vertex is and
    the UV-Coordinates on how texture is applied onto the vertex. The vertices are drawn
    based on how the indices selected
 *@*vertexID - used to store the pointer of the vertex array object (VAO)
 *@*bufferID - used to store the pointer of the vertex buffer object (VBO)
 *@*indicesID - used to store the pointer of the indices that tells
    the renderer how to draw the vertexes.
 *@width - The width of the Vertex Array Object
 *@height - The height of the Vertex Array Object
 */
void createVertex(GLuint *vertexID, GLuint *bufferID, GLuint *indicesID, int width, int height){
    // Create 4 vertices for the Vertex Array Object
    // The VertexData is initialized like this:
    // Format: { {x, y, z}, {s, t} }
    // Example: { {50, 30, 0.0f}, {0, 0} };
    VertexData v0 = { { width / 2, -height / 2, 0.0f }, { 0, 0 } };     // This vertex defines the Left-Top
    VertexData v1 = { { width / 2, height / 2, 0.0f }, { 0, 1 } };      // This vertex defines the Left-Bottom
    VertexData v2 = { { -width / 2, height / 2, 0.0f }, { 1, 1 } };     // This vertex defines the Right-Bottom
    VertexData v3 = { { -width / 2, -height / 2, 0.0f }, { 1, 0 } };    // This vertex defines the Right-Top

    // You may be confused to why the the Right side is -width and left side is width
    // It is because when the Camera views the front of the Vertex Array Object
    // The Camera's Left is the Vertex Array Object's Right

    VertexData vertices[] = { v0, v1, v2, v3 };

    // OpenGL draws vertices in counter-clockwise order,
    // So we create indices to create two triangles that form a square
    
    byte indices[] = {
        // Left-Bottom Triangle
        0, 1, 2,
        // Right-Top Triangle
        2, 3, 0
    };

    // Create a Vertex Array Object (VAO) in memory
    // And store the pointer to the memory into vertexID
    glGenVertexArrays(1, vertexID);

    // Next we select(Bind) the Vertex Array Object for editing
    glBindVertexArray(*vertexID);

    // Create a Vertex Buffer Object (VBO) in memory
    // And store the pointer to the memory into bufferID
    glGenBuffers(1, bufferID);

    // Next we select(Bind) the Vertex Buffer Object for editing
    glBindBuffer(GL_ARRAY_BUFFER, *bufferID);

    // Store the data into the buffer memory
    // We use GL_STREAM_DRAW to tell OpenGL that we will be
    // modifying the buffer once and it will be used a few times
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    // Now that we have stored the data into the buffer memory
    // We will use the data in that memory to tell OpenGL
    // The position of the vertex, and how the textures are drawn

    // We point to the position data in the buffer
    // glVertexAttribPointer is defined as this:
    // glVertexAttribPointer( attributeIndex, size of the data, datatype, to Normalize or not, stride, pointer to data);
    // A vertex object array can contain 16 Vertex Buffer Objects
    // which is contained into an attributeList
    // We can modify the elements in the attributeList by
    // using the attributeIndex
    // Stride is the offset in bytes between each vertex
    // In this case the offset is the struct: VertexData
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, positionCoordinates));

    // Next we want to point to our texture coordinate data in the buffer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, textureCoordinates));

    // Deselect the Vertex Buffer Object from further editing
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Deselect the Vertex Array Object from further editing
    glBindVertexArray(0);

    // We create a Vertex Buffer Object for the indices
    glGenBuffers(1, indicesID);

    // Select the new Vertex Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indicesID);

    // Next we store the indices data into memory
    // We use GL_STATIC_DRAW because we are going to modify it once
    // And use it to draw many times
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Deselect the Vertex Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*
 *@Description: Loads and buffers the Image into memory
 *@fileName - Filepath of the image
 *@textureUnit - The texture unit this is buffering for
 */
GLuint loadAndBufferImage(const char* fileName, int textureUnit){

}
