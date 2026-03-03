#include "graph.h"
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <stdio.h>

#define RMI_BASE_LIST_SIZE 2

void RMIUtilAddToGraph(RMI_Node *parent, void *data, RMI_InsertType type)
{
    switch (type)
    {
    case RMI_REPLACE:
        
        break;
    case RMI_APPEND:
        
        break;
    default:
        fprintf(stderr,"Wrong graph insert type.\n");
        break;
    }
}