#ifndef RMI_GLOBALS_H
#define RMI_GLOBALS_H

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

typedef struct {
    SDL_Window* window;
    Uint16 width;
    Uint16 height;
    bool running;
    float framePace;
    void (*eventHandler)();
    void (*updateHandler)();
    void (*drawHandler)();
}RMI_Globals;

volatile RMI_Globals* RMI_GetGlobals();

void RMI_R_SetupGlobals(volatile RMI_Globals* ptr);


#endif