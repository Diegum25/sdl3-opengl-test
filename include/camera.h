#pragma once
#include "cglm/cglm.h"

typedef struct 
{
    vec3 position;
    vec3 target;
    vec3 direction;
    vec3 rightAxis;
    vec3 upAxis;
}RMI_Camera;

void RMIInitCamera(RMI_Camera *camera);
void RMICameraUpdate(RMI_Camera *camera);
