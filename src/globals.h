#ifndef RMI_GLOBALS_H
#define RMI_GLOBALS_H

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

typedef struct {
    SDL_Window* window;
    Uint16 width;
    Uint16 height;
    bool running;
    float framePace;
    void (*eventHandler)(SDL_Event* event);
    void (*updateHandler)();
    void (*drawHandler)();
}RMI_Globals;

extern volatile RMI_Globals g_globals; // this is funky and i dont like it

#endif