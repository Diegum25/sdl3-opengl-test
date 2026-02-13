#include "camera.h"

void RMIInitCamera(RMI_Camera *camera)
{
    camera->position[0] = 0.0f;
    camera->position[1] = 0.0f;
    camera->position[2] = 3.0f;

    camera->target[0] = 0.0f;
    camera->target[1] = 0.0f;
    camera->target[2] = 0.0f;

    RMICameraUpdate(camera);
}

void RMICameraUpdate(RMI_Camera *camera)
{
    glm_vec3_sub(camera->position,camera->target,camera->direction);
    glm_normalize(camera->direction);

    vec3 up = {0.0f,1.0f,0.0f};
    glm_vec3_cross(up,camera->direction,camera->rightAxis);
    glm_normalize(camera->rightAxis);

    glm_vec3_cross(camera->direction,camera->rightAxis,camera->upAxis);
}