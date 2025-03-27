#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
// TODO(student): Declare various other uniforms

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.

    vec4 color = texture2D(texture_1, texcoord);
    if (color.w < 0.5)
    {
        discard;
    }
    vec4 color2 = texture2D(texture_2, texcoord);
    if (color2.w < 0.5)
    {
        discard;
    }
    out_color = mix(color, color2, 0.5);
}
