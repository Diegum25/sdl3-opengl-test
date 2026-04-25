#ifndef RMI_SCENE_TREE_INTERNAL_H
#define RMI_SCENE_TREE_INTERNAL_H

#define RMI_TREE_POOL_SIZE 2048 // same as hl

typedef struct treeNode_s{
    unsigned int parentID;
    unsigned int* childrenID;
} RMI_TreeNode;

typedef struct tree_s{ // no scene only tree
    RMI_TreeNode pool[RMI_TREE_POOL_SIZE]; // malloc also has to find a slot dealwidit
} RMI_Tree;

#endif