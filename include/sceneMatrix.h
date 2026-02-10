#include <cglm/cglm.h>

typedef struct {
    mat4 model;
    mat4 view;
    mat4 projection;
} sceneMatrix;

void initSceneMatrix(sceneMatrix*, float w, float h);