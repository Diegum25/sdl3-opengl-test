#include "cpptest.hpp"
#include "cpptest.h"

// Externs arent needed here apparently
// This is all very convoluted and reminds me of half-life modding and having to modify 5 files to add a weapon.

int TestClass::getCoolInt()
{
    return this->coolInt;
}

TestClass* TestClass_Create(){
    return new TestClass();
};
int TestClass_GetCoolInt(TestClass* C){
    return C->getCoolInt();
};

// Node

void Node::AddChild(Node* Child){
    this->children.insert(this->children.end(),Child);
}

Node* Node_Create(){
    return new Node();
}

void Node_AddChild(Node* node, Node* child){
    node->AddChild(child);
};