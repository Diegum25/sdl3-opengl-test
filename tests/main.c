#define RMI_MAIN
#include "rmi_main.h"

#include "SDL3/SDL.h"
#include "test.h"
#include "stdlib.h"

void RMI_Init(void** appstate){
    *appstate = malloc(sizeof(int));
    **(int**)appstate = 2;

    SDL_Log("hi the RMI appstate points to %d\n",**(int**)appstate);
}

void RMI_Update(void* appstate){
    //SDL_Log("%d\n",*(int*)appstate);
}