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

// Value noise by Inigo Quilez - iq/2013
// https://www.shadertoy.com/view/lsf3WH
float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);
    vec2 u = f*f*(3.0-2.0*f);
    return mix( mix( random( i + vec2(0.0,0.0) ),
                     random( i + vec2(1.0,0.0) ), u.x),
                mix( random( i + vec2(0.0,1.0) ),
                     random( i + vec2(1.0,1.0) ), u.x), u.y);
}

mat2 rotate2d(float angle){
    return mat2(cos(angle),-sin(angle),
    sin(angle),cos(angle));
}

float lines(in vec2 pos, float b){
    float scale = 10.0;
    pos *= scale;
    return smoothstep(0.0,
                      .5+b*.5,
                      abs((sin(pos.x*3.1415)+b*2.0))*.5);
}

void main() {
    vec2 st = frag_position.xz;
    st /= 30;
    vec2 pos = st.yx*vec2(10.,3.);

    float pattern = pos.x;

    // Add noise
    pos = rotate2d( noise(pos) ) * pos;

    // Draw lines
    pattern = lines(pos,.5);

//    out_color = vec4(vec3(pattern),1.0);

    vec3 c1 = vec3(204.0/255.0, 204.0/255.0 ,0.0/255.0);
    vec3 c2 = vec3(1, 255.0/255.0, 0);
    out_color = vec4(mix(c1, c2, pattern), 1);
}