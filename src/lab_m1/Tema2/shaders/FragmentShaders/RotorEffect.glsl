#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_color1;
in vec3 frag_color2;
in vec3 frag_position;
in float frag_time;
in float frag_resolution;
in vec3 frag_camera_position;
in vec3 frag_fog_color;

// Output
layout(location = 0) out vec4 out_color;

void main() {
    vec3 dist = frag_position - frag_camera_position;
    float dist_to_camera = length(dist);
    float fog_factor = clamp(dist_to_camera / 2000, 0, 1);

    out_color = vec4(mix(frag_color1, frag_fog_color, fog_factor), 0.1);
}