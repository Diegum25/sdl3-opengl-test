#ifndef RMI_SCENE_INTERNAL_H
#define RMI_SCENE_INTERNAL_H

#include "camera.h"
#include "sceneMatrix.h"
#include <SDL3/SDL.h>

typedef struct{
    RMI_Camera camera;
    RMI_SceneMatrix matrix;
} RMI_Scene;

void RMIInitScene(RMI_Scene* scene, SDL_Window* window);
#endif