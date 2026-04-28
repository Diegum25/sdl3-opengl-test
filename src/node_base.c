#include "SDL/SDL.h"
#include "node_base.h"
RMI_Node* RMICreateNodeBase(){
    RMI_Node* ptr = SDL_malloc(sizeof(RMI_Node));
    ptr->children = NULL;
    return ptr;
}