#include "RMI/rmi.h"
#include "globals.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_thread.h>
#include <SDL3/SDL_video.h>

volatile RMI_Globals* r_globals = NULL;

void RMI_R_SetupGlobals(volatile RMI_Globals* ptr){
    r_globals = ptr;
}

int RMI_I_Update(void* data){ // This is not on the main thread
    const float tickPace = (1.0f/64.0f);
    const Uint64 tickPaceNS = tickPace * 1000000000;
    while(r_globals->running){
        Uint64 start = SDL_GetTicksNS();
        r_globals->updateHandler();
        Uint64 end = SDL_GetTicksNS();

        Uint64 elapsed = end - start;

        if (elapsed < tickPaceNS) SDL_DelayPrecise(tickPaceNS - elapsed); // this approach kinda slaps
    }
    return 0;
};

void RMI_I_Draw(){ // This is on the main thread
    const Uint64 framePaceNS = (r_globals->framePace) * 1000000000;
    SDL_Event* events = SDL_calloc(sizeof(SDL_Event), 32);
    while(r_globals->running){
        Uint64 start = SDL_GetTicksNS();
        r_globals->drawHandler();
        SDL_PumpEvents();
        int eventsGot = SDL_PeepEvents(events, 32, SDL_GETEVENT, SDL_EVENT_FIRST, SDL_EVENT_LAST);
        if(eventsGot != -1){
            for(Uint16 i = 0; i < eventsGot; i++){
                r_globals->eventHandler(&events[i]);
            }
        }
        SDL_GL_SwapWindow(r_globals->window);
        Uint64 end = SDL_GetTicksNS();

        Uint64 elapsed = end - start;

        if (elapsed < framePaceNS) SDL_DelayPrecise(framePaceNS - elapsed); // this approach kinda slaps
    }
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

RMI_Result RMI_Stop(){
    if(!r_globals->running) return RMI_RESULT_FAILURE;
    r_globals->running = false;
    return RMI_RESULT_SUCCESS;
}