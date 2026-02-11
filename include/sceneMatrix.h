#pragma once

#include <cglm/cglm.h>

typedef struct {
    mat4 model;
    mat4 view;
    mat4 projection;
} RMI_SceneMatrix;

void RMIInitSceneMatrix(RMI_SceneMatrix*, float w, float h);