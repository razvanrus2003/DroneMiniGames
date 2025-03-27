#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_normal;
in vec3 frag_tex;
in vec3 frag_color;
in vec3 frag_position;
in float frag_time;

// Output
layout(location = 0) out vec4 out_color;

// 2D Random
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}

// 2D Noise based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
    (c - a)* u.y * (1.0 - u.x) +
    (d - b) * u.x * u.y;
}

void main()
{
    // TODO(student): Write pixel out color
    vec2 st = frag_position.xz;
//    st = vec2(frag_position.x + frag_position.z, frag_time);

    st *= 2;
    vec3 c1 = vec3(107.0/255.0, 37.0/255.0 ,7.0/255.0);
    vec3 c2 = vec3(0, 102.0/255.0, 0);

//    vec3 c1 = vec3(0.0/255.0, 0.0/255.0 ,255.0/255.0);
//    vec3 c2 = vec3(0, 0.0/204.0, 0);
    out_color = vec4(mix(c1, c2, noise(st / 5)), 1);
}
