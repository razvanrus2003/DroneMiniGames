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

vec2 skew (vec2 st) {
    vec2 r = vec2(0.0);
    r.x = 1.1547*st.x;
    r.y = st.y+0.5*r.x;
    return r;
}

vec3 simplexGrid (vec2 st) {
    vec3 xyz = vec3(0.0);

    vec2 p = fract(skew(st));
    if (p.x > p.y) {
        xyz.xy = 1.0-vec2(p.x,p.y-p.x);
        xyz.z = p.y;
    } else {
        xyz.yz = 1.0-vec2(p.x-p.y,p.y);
        xyz.x = p.x;
    }

    return fract(xyz);
}

void main() {
    vec2 st = frag_position.xz;
    vec3 color = vec3(0.0);

    // Scale the space to see the grid
    st *= 10.;

    // Show the 2D grid
//    color.rg = fract(st);

    // Skew the 2D grid
//     color.rg = fract(skew(st));

    // Subdivide the grid into to equilateral triangles
     color = simplexGrid(st);

    out_color = vec4(color,1.0);
}