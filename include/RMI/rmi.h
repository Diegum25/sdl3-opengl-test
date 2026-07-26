#ifndef RMI_H
#define RMI_H

#include "SDL3/SDL.h"

typedef enum RMI_Result{
    RMI_RESULT_SUCCESS,
    RMI_RESULT_FAILURE
}RMI_Result;

extern RMI_Result RMI_Init(Uint16 width, Uint16 height, Uint16 framerate, void(*event), void(*update), void(*draw));
extern RMI_Result RMI_Deinit();

extern bool RMI_KeepRunning();
extern void RMI_HandleEvents();
extern void RMI_Update();
extern void RMI_Draw();

extern void RMI_StopRunning();

extern void RMI_Log(SDL_PRINTF_FORMAT_STRING const char *fmt, ...);

#endif