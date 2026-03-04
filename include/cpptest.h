#pragma once

// This is what C will see

#ifdef __cplusplus
extern "C"{
#endif

typedef struct TestClass TestClass; // class to struct?

TestClass* TestClass_Create();
int TestClass_GetCoolInt(TestClass*);

typedef struct Node Node;

Node* Node_Create();
void Node_AddChild(Node* node, Node* child);


#ifdef __cplusplus
}
#endif