#include "SDL3/SDL.h"
#include "globals.h"
#include "glad/gl.h"

bool RMI_Init(unsigned int x, unsigned int y){

    RMI_Globals* globals = RMI_GetGlobals();

    globals->test = 1111111;

    SDL_Log("Global test: %d",globals->test);
    return true;
}