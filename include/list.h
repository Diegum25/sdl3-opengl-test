#pragma once

#include <SDL3/SDL.h>
#include <stdlib.h>

typedef struct{
    void* data;
    void* previous;
    void* next;
}RMI_list_object;

typedef struct{ // wild data realloc would be a better aproach.
    RMI_list_object* start;
    RMI_list_object* end;
}RMI_list;

void RMIUtilPushIntoList(RMI_list* p_list,void* thing); // USAGE: RMIUtilPushIntoList(&list, (void*)&thing) WHERE [THING] WAS ALLOCATE WITH MALLOC.