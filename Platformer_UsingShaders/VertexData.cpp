#include "VertexData.h"

void setupVertexDataQuad(VertexData *quad, int width, int height){
    //Vertices
    // initialized as such:
    // {position data}, {color data}, {UV-Mapping Data}
    VertexData v0 = { { 0.0f, (float)height, 0.0f }, { 0, 0 } }; // Left-Top
    VertexData v1 = { { 0.0f, 0.0f, 0.0f }, { 0, 1 } }; // Left-Bottom
    VertexData v2 = { { -(float)width, 0.0f, 0.0f }, { 1, 1 } }; // Right-Bottom
    VertexData v3 = { { -(float)width, -(float)height, 0.0f }, { 1, 0 } }; // Right-Top
    
    VertexData quadVertices[4] = { v0, v1, v2, v3 };

    quad[0] = v0;
    quad[1] = v1;
    quad[2] = v2;
    quad[3] = v3;
}