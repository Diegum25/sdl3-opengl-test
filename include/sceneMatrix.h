#include <cglm/cglm.h>

struct sceneMatrix{
    mat4 model;
    mat4 view;
    mat4 projection;
};

void initSceneMatrix(struct sceneMatrix*, float w, float h);