#pragma once

typedef struct{
    float* verts;
    unsigned int* indexes;
    unsigned int vertsAmnt;
    unsigned int indexAmnt;
} RMI_obj;


void RMILoadOBJ(RMI_obj* obj, const char* filename);