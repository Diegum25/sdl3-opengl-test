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

typedef struct PolymorphismInCWTF PolymorphismInCWTF;

PolymorphismInCWTF* PolymorphismInCWTF_Create(void (*SDL_Log)(const char* fmt, ...),const char* text);
void PolymorphismInCWTF_Activate(PolymorphismInCWTF* C);

// general

void Node_Activate_Children(Node* N);

#ifdef __cplusplus
}
#endif