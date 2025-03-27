//
// Created by razvan on 12/1/24.
//

#include "Terrain.h"
#include <iostream>
Terrain::Terrain(int vertexCount, vec3 scale, float resolution) : vertexCount(vertexCount), scale(scale), resolution(resolution) {
    heights = vector<vector<double>>(this->vertexCount, vector<double>(this->vertexCount, 0));
    std::cout << scale << std::endl;
    for (int i = 0; i < this->vertexCount; i++) {
        for (int j = 0; j < this->vertexCount; j++) {
            heights[i][j] = mix(0., 4., noise(vec<2, double>((double)i * resolution * scale.x, (double)j * resolution * scale.x)) * .5 + .5 ) +
                 mix(0., 20., noise(vec<2, double>(i * (resolution / 8) * scale.x, j * (resolution / 8) * scale.x)) * .5 + .5 );
            heights[i][j] = heights[i][j] * scale.y;
        }
    }
}

float Terrain::getHeights(float x, float z) {
    int x1 = (int)floor(x / scale.x);
    int z1 = (int)floor(z / scale.z);

    if (x1 <= 0 || z1 <= 0 || x1 >= vertexCount - 1 || z1 >= vertexCount - 1) {
        return 1;
    }
    int x2 = x1 + 1;
    int z2 = z1 + 1;

    x /= scale.x;
    z /= scale.z;

    float distx1 = (float) (x - x1);
    float distz1 = (float) (z - z1);
    float distx2 = (float) (x2 - x);
    float distz2 = (float) (z2 - z);

    double ret = heights[x1][z1] * distx2 * distz2 +
                heights[x2][z1] * distx1 * distz2 +
                heights[x1][z2] * distx2 * distz1 +
                heights[x2][z2] * distx1 * distz1;
    return ret;
}

Terrain::Terrain() {
}

Terrain::~Terrain() {
}

vec<3, double> operator*(vec<3, double> a, vec<3, double> b) {
    return vec<3, double>(a.x * b.x, a.y * b.y, a.z * b.z);
}

vec<3, double> operator*(vec<3, double> a, double b) {
    return vec3(a.x * b, a.y * b, a.z * b);
}

vec<3, double> operator*(double a, vec<3, double> b) {
    return vec3(a * b.x, a * b.y, a * b.z);
}

vec<2, double> operator*(vec<2, double> a, vec<2, double> b) {
    return vec2(a.x * b.x, a.y * b.y);
}

vec<2, double> operator*(vec<2, double> a, double b) {
    return vec<2, double>(a.x * b, a.y * b);
}

vec<3, double> operator+(vec<3, double> a, double b) {
    return vec<3, double>(a.x + b, a.y + b, a.z + b);
}

vec<3, double> operator-(double a, vec<3, double> b) {
    return vec<3, double>(a - b.x, a - b.y, a - b.z);
}

vec<3, double> operator-(vec<3, double> a, double b) {
    return vec<3, double>(a.x - b, a.y - b, a.z - b);
}

float max (double a, double b) {
    return a > b ? a : b;
}

vec<3, double> max(vec<3, double> a, double b) {
    return vec<3, double>(max(a.x, b), max(a.y, b), max(a.z, b));
}

vec<3, double> mod289(vec<3, double> x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec<2, double> mod289(vec<2, double> x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec<3, double> permute(vec<3, double> x) { return mod289(((x * 34.0)+1.0)*x); }

double Terrain::noise(vec<2, double> v) {
    // Precompute values for skewed triangular grid
    vec<4, double> C = vec<4, double>(0.211324865405187,
    // (3.0-sqrt(3.0))/6.0
    0.366025403784439,
    // 0.5*(sqrt(3.0)-1.0)
    -0.577350269189626,
    // -1.0 + 2.0 * C.x
    0.024390243902439);
    // 1.0 / 41.0

    // First corner (x0)
    vec<2, double> i  = floor(v + dot(v, vec<2, double>(C.y, C.y)));
    vec<2, double> x0 = v - i + dot(i, vec<2, double>(C.x, C.x));

    // Other two corners (x1, x2)
    vec<2, double> i1 = vec<2, double>(0.0);
    i1 = (x0.x > x0.y)? vec<2, double>(1.0, 0.0):vec<2, double>(0.0, 1.0);
    vec<2, double> x1 = vec<2, double>(x0.x, x0.y) + vec<2, double>(C.x, C.x) - i1;
    vec<2, double> x2 = vec<2, double>(x0.x, x0.y) + vec<2, double>(C.z, C.z);

    // Do some permutations to avoid
    // truncation effects in permutation
    i = mod289(i);
    vec<3, double> p = permute(
        permute( i.y + vec<3, double>(0.0, i1.y, 1.0))
        + i.x + vec<3, double>(0.0, i1.x, 1.0 ));

    vec<3, double> m = max(0.5 - vec<3, double>(
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

    vec<3, double> x = 2.0 * fract(p * vec<3, double>(C.w, C.w, C.w)) - 1.0;
    vec<3, double> h = abs(x) - 0.5;
    vec<3, double> ox = floor(x + 0.5);
    vec<3, double> a0 = x - ox;

    // Normalise gradients implicitly by scaling m
    // Approximation of: m *= inversesqrt(a0*a0 + h*h);
    m *= 1.79284291400159 - 0.85373472095314 * (a0*a0+h*h);

    // Compute final noise value at P
    vec<3, double> g = vec<3, double>(0.0);
    g.x  = a0.x  * x0.x  + h.x  * x0.y;
    g.y = a0.y * x1.x + h.y * x1.y;
    g.z = a0.z * x2.x + h.z * x2.y;
    // g.yz = a0.yz * vec2(x1.x,x2.x) + h.yz * vec2(x1.y,x2.y);
    return 130.0 * dot(m, g);
}

