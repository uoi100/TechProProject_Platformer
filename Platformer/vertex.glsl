#version 150 core

in vec3 in_Position;
in vec4 in_Color;
in vec2 in_TextureCoord;

out vec4 pass_Color;
out vec2 pass_TextureCoord;

uniform mat4 mvp;

void main(void) {
    // Override gl_Position with our new calculated position
    vec4 v = vec4(in_Position, 1); // Transform an homogenous 4D vector
    gl_Position = mvp * v;

	pass_Color = in_Color;
    pass_TextureCoord = in_TextureCoord;
}