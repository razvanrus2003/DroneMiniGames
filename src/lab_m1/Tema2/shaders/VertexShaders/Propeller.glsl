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
//    frag_position = (Model * vec4(v_position, 1)).xyz;
    frag_position = v_position;
    frag_resolution = Resolution;
    frag_camera_position = CameraPosition;
    frag_fog_color = FogColor;

    // TODO(student): Compute gl_Position
    vec3 v_new_position = v_position;
    if (v_position.y > 0.5) {
        v_new_position.x = v_position.x * 0.7;
        v_new_position.z = v_position.z * 0.7;
    }

    if (v_position.y < -0.5) {
        v_new_position.x = v_position.x * 0.7;
        v_new_position.z = v_position.z * 0.7;
    }
    gl_Position = Projection * View * Model * vec4(v_new_position, 1.0);
}
