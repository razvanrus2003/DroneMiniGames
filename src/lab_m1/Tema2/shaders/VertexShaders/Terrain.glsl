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

vec3 mod289(vec3 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec2 mod289(vec2 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec3 permute(vec3 x) { return mod289(((x*34.0)+1.0)*x); }

//
// Description : GLSL 2D simplex noise function
//      Author : Ian McEwan, Ashima Arts
//  Maintainer : ijm
//     Lastmod : 20110822 (ijm)
//     License :
//  Copyright (C) 2011 Ashima Arts. All rights reserved.
//  Distributed under the MIT License. See LICENSE file.
//  https://github.com/ashima/webgl-noise
//
float snoise(vec2 v) {

	// Precompute values for skewed triangular grid
	const vec4 C = vec4(0.211324865405187,
	// (3.0-sqrt(3.0))/6.0
	0.366025403784439,
	// 0.5*(sqrt(3.0)-1.0)
	-0.577350269189626,
	// -1.0 + 2.0 * C.x
	0.024390243902439);
	// 1.0 / 41.0

	// First corner (x0)
	vec2 i  = floor(v + dot(v, C.yy));
	vec2 x0 = v - i + dot(i, C.xx);

	// Other two corners (x1, x2)
	vec2 i1 = vec2(0.0);
	i1 = (x0.x > x0.y)? vec2(1.0, 0.0):vec2(0.0, 1.0);
	vec2 x1 = x0.xy + C.xx - i1;
	vec2 x2 = x0.xy + C.zz;

	// Do some permutations to avoid
	// truncation effects in permutation
	i = mod289(i);
	vec3 p = permute(
		permute( i.y + vec3(0.0, i1.y, 1.0))
		+ i.x + vec3(0.0, i1.x, 1.0 ));

	vec3 m = max(0.5 - vec3(
	dot(x0,x0),
	dot(x1,x1),
	dot(x2,x2)
	), 0.0);

	m = m*m ;
	m = m*m ;

	// Gradients:
	//  41 pts uniformly over a line, mapped onto a diamond
	//  The ring size 17*17 = 289 is close to a multiple
	//      of 41 (41*7 = 287)

	vec3 x = 2.0 * fract(p * C.www) - 1.0;
	vec3 h = abs(x) - 0.5;
	vec3 ox = floor(x + 0.5);
	vec3 a0 = x - ox;

	// Normalise gradients implicitly by scaling m
	// Approximation of: m *= inversesqrt(a0*a0 + h*h);
	m *= 1.79284291400159 - 0.85373472095314 * (a0*a0+h*h);

	// Compute final noise value at P
	vec3 g = vec3(0.0);
	g.x  = a0.x  * x0.x  + h.x  * x0.y;
	g.yz = a0.yz * vec2(x1.x,x2.x) + h.yz * vec2(x1.y,x2.y);
	return 130.0 * dot(m, g);
}

void main()
{
    // TODO(student): Send output to fragment shader
	frag_color1 = Color1;
	frag_color2 = Color2;
	frag_time = Time;
//	frag_position = v_position;
	frag_position = (Model * vec4(v_position, 1)).xyz;
	frag_resolution = Resolution;
	frag_camera_position = CameraPosition;
	frag_fog_color = FogColor;

	// TODO(student): Compute gl_Position
	float new_y = mix(0, 4, snoise(frag_position.xz * Resolution)*.5+.5) + mix(0, 20, snoise(frag_position.xz * (Resolution/8))*.5+.5);

	gl_Position = Projection * View * Model * vec4(v_position[0], new_y, v_position[2], 1.0);
}
