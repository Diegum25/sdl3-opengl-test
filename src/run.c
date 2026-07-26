#include "RMI/rmi.h"
#include "globals.h"

void RMI_StopRunning(){
    volatile RMI_Globals* globals = RMI_GetGlobals();
    globals->iWantToKeepRunning = false;
}

bool RMI_KeepRunning(){ // this has to sleep the thread to the desired framerate
    volatile const RMI_Globals* globals = RMI_GetGlobals();
    return globals->iWantToKeepRunning;
};

void RMI_HandleEvents(){
    volatile const RMI_Globals* globals = RMI_GetGlobals();
    globals->eventHandler();
};

void RMI_Update(){
    volatile const RMI_Globals* globals = RMI_GetGlobals();
    globals->updateHandler();
};

void RMI_Draw(){
    volatile const RMI_Globals* globals = RMI_GetGlobals();
    globals->drawHandler();
};
