#include "RMI/rmi.h"
#include "globals.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_thread.h>
#include <SDL3/SDL_video.h>

volatile RMI_Globals* r_globals = NULL;
int vsync;

void RMI_R_SetupGlobals(volatile RMI_Globals* ptr){
    r_globals = ptr;
}

int RMI_I_Update(void* data){ // This one has to wait tickrate delta time
    const float tickPace = 1.0f / 64.0f;
    r_globals->updateHandler();
    return 0;
};

void RMI_I_Draw(){ // This one for framerate delta time
    r_globals->drawHandler();
};

RMI_Result RMI_Run(){

    if(r_globals == NULL){
        return RMI_RESULT_FAILURE;
    }

    if(r_globals->running){
        return RMI_RESULT_FAILURE;
    }

    SDL_Log("heheh the framepace is %f\n",r_globals->framePace);

    r_globals->running = true;

    SDL_Thread* thr = SDL_CreateThread(RMI_I_Update,"UpdateThread",NULL);
    SDL_DetachThread(thr);

    RMI_I_Draw();

    return RMI_RESULT_SUCCESS;
}