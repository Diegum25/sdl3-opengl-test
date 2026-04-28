#include "globals.h"

static RMI_Globals g_globals;

RMI_Globals* RMIGetGlobals(){
    return &g_globals;
};