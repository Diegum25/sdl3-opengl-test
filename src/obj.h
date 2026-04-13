#pragma once
typedef struct {
    float* verts;
    unsigned int tris;
    unsigned int quads;
    const char* fileName;
} obj_data;

obj_data getObjData(const char* objPath);