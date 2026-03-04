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
}

// polymorphclass

PolymorphismInCWTF::PolymorphismInCWTF(void (*SDL_Log)(const char *fmt, ...), const char *text)
{
    this->SDL_Log = SDL_Log;
    this->text = text;
}

void PolymorphismInCWTF::Activate()
{
    (*this->SDL_Log)("%s",this->text);
}

PolymorphismInCWTF *PolymorphismInCWTF_Create(void (*SDL_Log)(const char *fmt, ...), const char *text)
{
    return new PolymorphismInCWTF(SDL_Log,text);
}
void PolymorphismInCWTF_Activate(PolymorphismInCWTF* C) {
    C->Activate();
}

// General
void Node_Activate_Children(Node *N) {
    for(Node* i : N->children){ // i genuinely couldnt replicate this in C and just wanted an easy solution
        i->Activate();
    }
};