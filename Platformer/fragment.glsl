#version 330 core

uniform sampler2D texture_diffuse;

in vec4 pass_Color;
in vec2 pass_TextureCoord;

out vec4 out_Color;

void main(void) {
    // get our texture ready for rendering
    vec4 textRender = texture(texture_diffuse, pass_TextureCoord);

    // If the alpha of the texture is below 0.1 then discard the shader / don't bother rendering.
    if(textRender.a < 0.1)
        discard;

    //Render the texture
    out_Color = textRender;
}