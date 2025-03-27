#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec3 v_tex;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;
uniform vec3 Color1;
uniform vec3 Color2;
uniform float Resolution;
uniform vec3 CameraPosition;
uniform vec3 FogColor;
// Output
// TODO(student): Output values to fragment shader
out vec3 frag_color1;
out vec3 frag_color2;
out vec3 frag_position;
out float frag_time;
out float frag_resolution;
out vec3 frag_camera_position;
out vec3 frag_fog_color;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_color1 = Color1;
    frag_color2 = Color2;
    frag_time = Time;
    frag_position = (Model * vec4(v_position, 1)).xyz;
    frag_resolution = Resolution;
    frag_camera_position = CameraPosition;
    frag_fog_color = FogColor;

    float time = Time * 1000;
    mat4 rotationOy = mat4(
        vec4(cos(time), 0, sin(time), 0),
        vec4(0, 1, 0, 0),
        vec4(-sin(time), 0, cos(time), 0),
        vec4(0, 0, 0, 1)
    );

    mat4 scale = mat4(
        vec4(1.9, 0, 0, 0),
        vec4(0, 0.01, 0, 0),
        vec4(0, 0, 0.09, 0),
        vec4(0, 0, 0, 1)
    );

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
