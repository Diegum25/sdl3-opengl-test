#pragma once
#include "cglm/cglm.h"

typedef struct {
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 speed;
    vec3 view;
    float yaw;
    float pitch;
    float fov;
}RMI_Camera;

void RMIInitCamera(RMI_Camera *camera);

void RMICameraFlight(RMI_Camera* camera, vec2 movementVec);

void RMICameraFloat(RMI_Camera* camera, vec2 movementVec); // we all float (pennywise booty cheeks)