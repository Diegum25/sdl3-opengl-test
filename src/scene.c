#include "scene.h"

void RMIInitScene(RMI_Scene* scene, SDL_Window* window){
    int x,y;
    SDL_GetWindowSizeInPixels(window,&x,&y);
    RMIInitCamera(&scene->camera);
    RMIInitSceneMatrix(&scene->matrix,x,y);
    scene->root = Node_Create();
}