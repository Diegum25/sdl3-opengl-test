#include "globals.h"

volatile RMI_Globals globals = {0};

volatile RMI_Globals* RMI_GetGlobals(){
    return &globals;
};