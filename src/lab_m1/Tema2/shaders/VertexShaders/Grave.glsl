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
out vec4 real_position;

void main()
{
    mat4 i = inverse(Model);
    // TODO(student): Send output to fragment shader
    frag_color1 = Color1;
    frag_color2 = Color2;
    frag_time = Time;
    frag_position = v_position;
    frag_resolution = Resolution;
    frag_camera_position = CameraPosition;
    frag_fog_color = FogColor;

    vec3 new_pos = v_position;

    float rand = frag_resolution;

    if (v_position.y < -.5) {
        new_pos.z += sign(v_position.z) * abs(sin(rand) * 0.7);
        new_pos.y *= abs(sin(rand))*.5 + 1;
        new_pos.x += -sign(v_position.x) * abs(sin(rand) * 0.2);

    } else if (v_position.y >= 0) {
        new_pos.y *= abs(sin(rand))*.5 + .4;

        if (v_position.y > 0)
            new_pos.y += abs(sin(rand)) * 0.2;
    }

    real_position = Model * vec4(new_pos, 1.0);

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * real_position;
}
