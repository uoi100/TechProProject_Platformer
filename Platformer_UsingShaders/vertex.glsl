#version 150 core

in vec2 in_Position;
in vec4 in_Color;
in vec2 in_TextureCoord;

out vec4 pass_Color;
out vec2 pass_TextureCoord;

uniform mat4 trans;

void main(void) {
    // Override gl_Position with our new calculated position
    gl_Position = trans * vec4(in_Position, 0.0, 1.0);

	pass_Color = in_Color;
    pass_TextureCoord = in_TextureCoord;
}