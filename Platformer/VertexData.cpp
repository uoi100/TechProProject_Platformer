#include "VertexData.h"

VertexData *makeVertices(int width, int height){
    VertexData *vertices = new VertexData[4];
    vertices[0] = { { -width / 2, -height / 2, 0.0f }, { 0.0f, 0.0f } }; // Bottom-Left
    vertices[1] = { { width / 2, -height / 2, 0.0f }, { 1.0f, 0.0f } }; // Bottom-Right
    vertices[2] = { { width / 2, height / 2, 0.0f }, { 1.0f, 1.0f } }; // Top-Right
    vertices[3] = { { -width / 2, height / 2, 0.0f }, { 0.0f, 1.0f } }; // Top-Left
    return vertices;
}

/*
std::vector<VertexData> makeVertices(int width, int height){
    std::vector<VertexData> vertices{
            { { -width/2, -height/2, 0.0f }, { 0.0f, 0.0f } },     // Bottom-Left
            { { width/2, -height/2, 0.0f }, { 1.0f, 0.0f } },   // Bottom-Right
            { { width/2, height/2, 0.0f }, { 1.0f, 1.0f } }, // Top-Right
            { { -width/2, height/2, 0.0f }, { 0.0f, 1.0f } }    // Top-Left
    };

    return vertices;
}
*/