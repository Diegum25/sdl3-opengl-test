#include "camera.h"
#include "SDL3/SDL.h"

void RMIInitCamera(RMI_Camera *camera)
{
    camera->position[0] = 0.0f;
    camera->position[1] = 0.0f;
    camera->position[2] = 3.0f;

    // this is local
    camera->front[0] = 0.0f;
    camera->front[1] = 0.0f;
    camera->front[2] = -1.0f;

    camera->up[0] = 0.0f;
    camera->up[1] = 1.0f;
    camera->up[2] = 0.0f;

    camera->pitch = 0.0f;
    camera->yaw = -90.0f;

    camera->fov = 45.0f;

    camera->speed[0] = 0.1f;
    camera->speed[1] = 0.1f;
    camera->speed[2] = 0.1f;

}

void RMICameraFlight(RMI_Camera *camera, vec2 movementVec)
{
    vec3 fowardMovement = {movementVec[1],movementVec[1],movementVec[1]};
    vec3 sideMovement = {movementVec[0],movementVec[0],movementVec[0]};

    glm_vec3_mul(fowardMovement,camera->speed,fowardMovement);
    glm_vec3_mul(sideMovement,camera->speed,sideMovement);

    vec3 movement; // general

    float yaw = SDL_atan2(camera->front[2],camera->front[0]);

    vec3 cutdownFront = {(float)SDL_cos(yaw),0.0f,(float)SDL_sin(yaw)};

    vec3 cameraSide = {-cutdownFront[2],0.0f,cutdownFront[0]};

    glm_vec3_mul(camera->front,fowardMovement,movement);

    glm_vec3_add(movement,camera->position,camera->position);

    glm_vec3_mul(cameraSide,sideMovement,movement);

    glm_vec3_add(movement,camera->position,camera->position);
}

void RMICameraFloat(RMI_Camera *camera, vec2 movementVec)
{
    vec3 fowardMovement = {movementVec[1],0.0f,movementVec[1]};
    vec3 sideMovement = {movementVec[0],0.0f,movementVec[0]};

    glm_vec3_mul(fowardMovement,camera->speed,fowardMovement);
    glm_vec3_mul(sideMovement,camera->speed,sideMovement);

    vec3 movement; // general

    float yaw = SDL_atan2(camera->front[2],camera->front[0]);

    vec3 cutdownFront = {(float)SDL_cos(yaw),0.0f,(float)SDL_sin(yaw)};

    vec3 cameraSide = {-cutdownFront[2],0.0f,cutdownFront[0]};

    glm_vec3_mul(cutdownFront,fowardMovement,movement);

    glm_vec3_add(movement,camera->position,camera->position);

    glm_vec3_mul(cameraSide,sideMovement,movement);

    glm_vec3_add(movement,camera->position,camera->position);
}
