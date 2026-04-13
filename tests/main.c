#define RMI_MAIN
#include "RMI/rmi_main.h" // this also includes a bunch of slop :D

#include "RMI/rmi.h"

RMI_Camera camera;

void RMI_Init(void** appstate){
    RMIInitCamera(&camera);
}

void RMI_Update(void* appstate){
    
}

void RMI_End(void *appstate){

}