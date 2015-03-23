#include "Prefix.h"

/*
 * Our Vertex Data Structure
 * Positons - The position of the vertex
 * color - The color of the Vertex
 * UVposition - The UV mapping for applying textures to the vertex
 * where U is the X position and V is the Y position, the origin of the mapping is at the top left.
 */
struct VertexData{
    GLfloat positions[2];
    GLfloat color[4];
    GLfloat UVPositions[2];
};