#ifndef RMI_H
#define RMI_H

#include "SDL3/SDL_stdinc.h"
#include <SDL3/SDL_events.h>

typedef enum RMI_Result{
    RMI_RESULT_SUCCESS,
    RMI_RESULT_FAILURE
}RMI_Result;

extern RMI_Result RMI_Init(Uint16 width, Uint16 height, void(*event)(SDL_Event* event), void(*update), void(*draw));
extern void RMI_Deinit();

extern RMI_Result RMI_Run();
extern RMI_Result RMI_Stop();

extern void RMI_Log(SDL_PRINTF_FORMAT_STRING const char *fmt, ...);

#endif