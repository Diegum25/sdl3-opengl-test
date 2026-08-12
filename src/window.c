#include "RMI/rmi.h"
#include "globals.h"
#include <SDL3/SDL_video.h>

volatile RMI_Globals* w_globals = NULL;

void RMI_W_SetupGlobals(volatile RMI_Globals* ptr){
    w_globals = ptr;
}

RMI_Result RMI_GetWindowSizeInPixels(int *w, int *h){
    if (!w_globals || !w_globals->window) return RMI_RESULT_FAILURE;

    if(SDL_GetWindowSizeInPixels(w_globals->window, w, h)){
        return RMI_RESULT_SUCCESS;
    }else {
        return RMI_RESULT_FAILURE;
    };
}