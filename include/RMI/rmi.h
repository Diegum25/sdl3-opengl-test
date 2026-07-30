#ifndef RMI_H
#define RMI_H

#include "SDL3/SDL_stdinc.h"

typedef enum RMI_Result{
    RMI_RESULT_SUCCESS,
    RMI_RESULT_FAILURE
}RMI_Result;

extern RMI_Result RMI_Init(Uint16 width, Uint16 height, void(*event), void(*update), void(*draw));
extern void RMI_Deinit();

extern RMI_Result RMI_Run();

extern void RMI_Log(SDL_PRINTF_FORMAT_STRING const char *fmt, ...);

#endif