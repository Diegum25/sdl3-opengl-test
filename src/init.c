#include "RMI/rmi.h"
#include "globals.h"
#include <SDL3/SDL_init.h>
#include <stdbool.h>

RMI_Result RMI_Init(Uint16 x, Uint16 y, Uint16 fps, void(*event), void(*update), void(*draw)){

    volatile RMI_Globals* globals = RMI_GetGlobals();

    globals->width = x;
    globals->height = y;

    globals->eventHandler = event;
    globals->updateHandler = update;
    globals->drawHandler = draw;

    globals->framerate = fps;

    if(!SDL_Init(SDL_INIT_VIDEO)) return RMI_RESULT_FAILURE;

    globals->iWantToKeepRunning = true;

    return RMI_RESULT_SUCCESS;
}

RMI_Result RMI_Deinit(){
    volatile RMI_Globals* glabas = RMI_GetGlobals();
    glabas->iWantToKeepRunning = false;
    
    SDL_Quit();
    return RMI_RESULT_SUCCESS; // :P
};