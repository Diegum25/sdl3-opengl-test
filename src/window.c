#include "RMI/rmi.h"
#include "globals.h"
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_video.h>


RMI_Result RMI_GetWindowSizeInPixels(int *w, int *h){
    if (!g_globals.window) return RMI_RESULT_FAILURE;

    if(SDL_GetWindowSizeInPixels(g_globals.window, w, h)) return RMI_RESULT_SUCCESS;
    return RMI_RESULT_FAILURE;
}

RMI_Result RMI_SetWindowRelativeMouseMode(bool enabled){
    if (!g_globals.window) return RMI_RESULT_FAILURE;
    if(SDL_SetWindowRelativeMouseMode(g_globals.window, enabled)) return RMI_RESULT_SUCCESS;
    return RMI_RESULT_FAILURE;
}