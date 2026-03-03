#pragma once

typedef enum RMI_InsertType{
    RMI_REPLACE,
    RMI_APPEND
}RMI_InsertType;

struct rmi_node{
    void* data;
    struct rmi_node* children;
    unsigned int count;
    unsigned int size;
};

typedef struct rmi_node RMI_Node;

typedef struct{
    RMI_Node* rootNode;
}RMI_Graph;

void RMIUtilAddToGraph(RMI_Node* parent, void* data, RMI_InsertType); // USAGE: RMIUtilAddToGraph(&node, (void*)&thing) WHERE [THING] WAS ALLOCATE WITH MALLOC. Node can be RMI_Graph.rootNode.
