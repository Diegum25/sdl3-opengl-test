#ifndef RMI_SCENE_TREE_INTERNAL_H
#define RMI_SCENE_TREE_INTERNAL_H

// nvm i dont think this is possible with static memory

// but i found out that you can downcast stuff setup like this
typedef struct SNode{
    // base stuff
} RMI_Node;

typedef struct SAnotherNode{
    RMI_Node super;
} RMI_AnotherNode;

#endif