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
vec2 random2(vec2 st){
    st = vec2( dot(st,vec2(127.1,311.7)),
    dot(st,vec2(269.5,183.3)) );
    return -1.0 + 2.0*fract(sin(st)*43758.5453123);
}

// Gradient Noise by Inigo Quilez - iq/2013
// https://www.shadertoy.com/view/XdXGW8
float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    vec2 u = f*f*(3.0-2.0*f);

    return mix( mix( dot( random2(i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                     dot( random2(i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                mix( dot( random2(i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),
                     dot( random2(i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
}

void main() {
    vec2 st = frag_position.xz;
    st.xy /= 30;
    vec3 color = vec3(0.0);

    float t = 1.0;
    // Uncomment to animate
//     t = abs(1.0-sin(frag_time*.1))*5.;
    // Comment and uncomment the following lines:
    st += noise(st*2.)*t; // Animate the coordinate space
    color = vec3(1.) * smoothstep(.18,.2,noise(st)); // Big black drops
    color += smoothstep(.15,.2,noise(st*10.)); // Black splatter
    color -= smoothstep(.35,.4,noise(st*10.)); // Holes on splatter

    out_color = vec4(1.-color,1.0);

    vec3 c1 = vec3(0.0/255.0, 0.0/255.0 ,204.0/255.0);
    vec3 c2 = vec3(1, 204.0/255.0, 0);
    out_color = vec4(mix(c1, c2, color), 1);
}