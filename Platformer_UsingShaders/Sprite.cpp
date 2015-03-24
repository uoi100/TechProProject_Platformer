#include "Sprite.h"

void Sprite::matrixTransformation(){
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;

    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
        );

    glm::vec3 up(0, 1, 0);

    //Movements
    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        0
    );

    //Matrix Transformations
    //Rules: M V P
    // M - Model
    // V - View
    // P - Projection
    glm::mat4 projection = glm::ortho(0.0f, -(float)winSize_.x, 0.0f, -(float)winSize_.y, -100.0f, 100.0f);

    glm::mat4 view = glm::lookAt(
        position_,
        position_ + direction,
        up
        );

    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 mvp = projection * view * model;

    GLuint matrixID = glGetUniformLocation(programID_, "mvp");

    // Send our transformations to the currently bound shader,
    // in the "mvp" uniform
    // for each model you render, since the MVP will be different
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(mvp));

}

void Sprite::checkButtons(){
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;

    glm::vec3 right(
        sin(horizontalAngle + 3.14f / 2.0f),
        0,
        0
    );

    glm::vec3 up(
        0,
        cos(verticalAngle),
        0
    );

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        position_ -= right * speed_;
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS)
        position_ += right * speed_;
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
        position_ += up * speed_;
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
        position_ -= up * speed_;

    std::stringstream ss;

    ss << "x: " << position_.x << " y: " << position_.y << " z: " << position_.z << std::endl;
    
    OutputDebugString(ss.str().c_str());
}

Sprite::Sprite(glm::vec2 size, glm::vec2 winSize)
    :size_{ size }, winSize_{ winSize }{
    //Setup Game Variables
    position_ = glm::vec3(0, 0, 3);
    speed_ = 10.0f;
}

void Sprite::setupShaders(GLuint vertexID, GLuint textureID, GLuint indicesID, GLuint programID, VertexData vertices[4]){
    vertexID_ = vertexID;
    textureID_ = textureID;
    indicesID_ = indicesID;
    programID_ = programID;

    for (int i = 0; i < 4; i++)
        vertices_[i] = vertices[i];
}

void Sprite::setPosition(glm::vec2 position){
    position_.x = position.x;
    position_.y = position.y;
}

void Sprite::render(){

    //Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID_);

    //Bind to the Vertex Object Array
    glBindVertexArray(vertexID_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID_);

    matrixTransformation();

    //Draw the vertices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    //Deselect
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void Sprite::update(){
    glBindBuffer(GL_ARRAY_BUFFER, vertexID_);

    checkButtons();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}