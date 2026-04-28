#include "RMI/RMI_nodes.h"
#include "RMI/RMI_tree.h"
#include "globals.h"
#include "node_base.h"
#include <assert.h>
#include <stddef.h>


RMI_Node* RMIGetRoot(){
    assert(RMIGetGlobals()->p_root != NULL);
    return RMIGetGlobals()->p_root;
};

void RMINodeAppend(RMI_Node* target, RMI_Node* node){
    if (target->children == NULL){
        
    }else {
        
    }
};