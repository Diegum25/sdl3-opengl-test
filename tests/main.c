#define RMI_MAIN
#include "rmi_main.h" // this also includes a bunch of slop :D
#include "rmi.h"

typedef struct{
    obj_data data;
} globalStupidStuff;

void RMI_Init(void** appstate){
    *appstate = SDL_malloc(sizeof(globalStupidStuff));
    globalStupidStuff* helper = *(globalStupidStuff**)appstate;
    helper->data = getObjData("const char *objPath");
    SDL_Log("%s\n",helper->data.fileName);
}

void RMI_Update(void* appstate){
    
}

void RMI_End(void *appstate){
    globalStupidStuff* helper = (globalStupidStuff*)appstate;
    SDL_Log("%s\n",helper->data.fileName);
    SDL_free(helper->data.verts);
}