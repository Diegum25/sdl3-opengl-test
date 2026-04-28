#ifndef RMI_P_NODES_H
#define RMI_P_NODES_H

typedef struct SNode RMI_Node;
/* typedef struct SAnotherNode RMI_Node_Another; */

enum ENodes{
    NODE_BASE
};

RMI_Node* RMICreateNode(enum ENodes,...);

RMI_Node* RMICreateNodeBase();

#endif