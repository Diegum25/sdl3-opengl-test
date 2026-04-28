#ifndef RMI_GLOBALS_H
#define RMI_GLOBALS_H

#include "RMI/RMI_nodes.h"
typedef struct SGlobals{
    RMI_Node* p_root;
} RMI_Globals;

static RMI_Globals g_globals;

#endif