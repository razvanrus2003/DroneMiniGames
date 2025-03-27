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
in vec4 real_position;

// Output
layout(location = 0) out vec4 out_color;

void main() {

    float color_factor = abs(frag_position.z) - 0.75;
    vec3 color;

    if (frag_position.y < 0) {
        vec2 dist = abs(vec2(frag_position.x, frag_position.z));
        float dist_to_center = length(dist) - 0.5;
        color = mix(frag_color1, frag_color2 / 3, dist_to_center / 2);
    } else {
//        vec2 dist = vec2(frag_position.x, frag_position.y);
        float dist_to_center = length(frag_position) - 0.5;
        color = mix(frag_color1, frag_color2 / 3, dist_to_center / 2);
    }

    vec3 dist = vec3(real_position) - frag_camera_position;
    float dist_to_camera = length(dist);
    float fog_factor = clamp(dist_to_camera / 2050, 0, 1);

    out_color = vec4(mix(color, frag_fog_color, fog_factor), 1);
}