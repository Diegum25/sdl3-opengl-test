#ifndef RMI_GLOBALS_H
#define RMI_GLOBALS_H

#include <SDL3/SDL_stdinc.h>

typedef struct {
    Uint16 width;
    Uint16 height;
    bool iWantToKeepRunning;
    Uint16 framerate;
    void (*eventHandler)();
    void (*updateHandler)();
    void (*drawHandler)();
}RMI_Globals;

volatile RMI_Globals* RMI_GetGlobals();

#endif