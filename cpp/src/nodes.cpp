#include "nodes.hpp"
#include "nodes.h"

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

// Model

Model::Model(void(*RMILoadOBJ)(RMI_obj*,const char*),const char* filename)
{
    RMILoadOBJ(&this->obj,filename); // RMILoadOBJ isnt getting built for this so im just gonna pass a pointer this codebase is a mess already wtf

    glGenVertexArrays(1,&this->VAO);
    glGenBuffers(1,&this->VBO);
    glGenBuffers(1,&this->EBO);

    if(this->obj.vertsAmnt == 0){
        return;
    }

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER,this->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->obj.vertsAmnt, this->obj.verts, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->obj.indexAmnt, this->obj.indexes,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

Model::~Model()
{
    free(this->obj.verts);
    free(this->obj.indexes);

    glDeleteVertexArrays(1,&this->VAO);
    glDeleteBuffers(1,&this->VBO);
    glDeleteBuffers(1,&this->EBO);
}

Model *Model_Create(void(*RMILoadOBJ)(RMI_obj*,const char*),const char* filename)
{
    return new Model(RMILoadOBJ,filename);
}