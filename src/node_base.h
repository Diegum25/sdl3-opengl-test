#ifndef RMI_NODE_BASE_H
#define RMI_NODE_BASE_H

#include "RMI/RMI_nodes.h"

// nvm i dont think this is possible with static memory

// but i found out that you can downcast stuff setup like this
struct SNode{
    struct SNode* children;
};

#endif