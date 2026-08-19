#include "RMI/rmi.h"
#include "globals.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mutex.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_thread.h>
#include <SDL3/SDL_video.h>

SDL_Mutex * mut;

int RMI_I_Update(void* data){ // This is not on the main thread
    const float tickPace = (1.0f/64.0f);
    const Uint64 tickPaceNS = tickPace * 1000000000;
    while(g_globals.running){
        Uint64 start = SDL_GetTicksNS();
        SDL_LockMutex(mut);
        g_globals.updateHandler();
        SDL_UnlockMutex(mut);
        Uint64 end = SDL_GetTicksNS();

        Uint64 elapsed = end - start;

        if (elapsed < tickPaceNS){
            SDL_DelayPrecise(tickPaceNS - elapsed);
        }
        else SDL_Log("[UPDATE] did not sleep\n"); // this approach kinda slaps
    }
    return 0;
};

void RMI_I_Draw(){ // This is on the main thread
    const Uint64 framePaceNS = (g_globals.framePace) * 1000000000;
    SDL_Event* events = SDL_calloc(sizeof(SDL_Event), 32);
    while(g_globals.running){
        Uint64 start = SDL_GetTicksNS();
        SDL_LockMutex(mut);
        g_globals.drawHandler();
        SDL_PumpEvents();
        int eventsGot = SDL_PeepEvents(events, 32, SDL_GETEVENT, SDL_EVENT_FIRST, SDL_EVENT_LAST);
        if(eventsGot != -1){
            for(Uint16 i = 0; i < eventsGot; i++){
                g_globals.eventHandler(&events[i]);
            }
        }
        SDL_GL_SwapWindow(g_globals.window);
        SDL_UnlockMutex(mut);
        Uint64 end = SDL_GetTicksNS();

        Uint64 elapsed = end - start;

        if (elapsed < framePaceNS) {
            SDL_DelayPrecise(framePaceNS - elapsed);
        }
        else SDL_Log("[DRAW] did not sleep\n"); // this approach kinda slaps
    }
};

RMI_Result RMI_Run(){
    if(g_globals.running){
        return RMI_RESULT_FAILURE;
    }

    SDL_Log("heheh the framepace is %f\n",g_globals.framePace);

    g_globals.running = true;

    mut = SDL_CreateMutex();

    SDL_Thread* thr = SDL_CreateThread(RMI_I_Update,"UpdateThread",NULL);
    SDL_DetachThread(thr);

    RMI_I_Draw();

    return RMI_RESULT_SUCCESS;
}

RMI_Result RMI_Stop(){
    if(!g_globals.running) return RMI_RESULT_FAILURE;
    g_globals.running = false;
    return RMI_RESULT_SUCCESS;
}