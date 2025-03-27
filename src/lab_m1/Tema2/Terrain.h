//
// Created by razvan on 12/1/24.
//
#pragma once
#include <vector>
#include "utils/glm_utils.h"

using namespace std;
using namespace glm;


class Terrain {
public:
    Terrain(int vertexCount, vec3 scale, float resolution);
    Terrain();
    ~Terrain();

    int vertexCount;
    vec3 scale;
    float resolution;
    vector<vector<double>> heights;

    double noise(vec<2, double> v);

    float getHeights(float x, float z);
};
