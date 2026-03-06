#include "../../glad/include/glad/glad.h" // long ass route
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
    this->children.push_back(Child);
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
Model::Model(const char* filename)
{
    this->obj = new RMI_Obj(filename);

    glGenVertexArrays(1,&this->VAO);
    glGenBuffers(1,&this->VBO);
    glGenBuffers(1,&this->EBO);

    if(this->obj->verts.size() == 0){
        return;
    }

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER,this->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->obj->verts.size(), this->obj->verts.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->obj->indexes.size(), this->obj->indexes.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

/*     for (int i = 0; i < this->obj->verts.size();i++){
        std::printf("%f\n",*(float*)(this->obj->verts.data() + i));
    }

    for (int i = 0; i < this->obj->indexes.size();i++){
        std::printf("%u\n",*(unsigned int*)(this->obj->indexes.data() + i));
    } */
}

Model::~Model()
{
    //std::printf("hi :)\n");
    delete this->obj; // can do this earlier

    glDeleteVertexArrays(1,&this->VAO);
    glDeleteBuffers(1,&this->VBO);
    glDeleteBuffers(1,&this->EBO);
}

Model *Model_Create(const char* filename)
{
    return new Model(filename);
}

void Model::Activate(){
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->obj->indexes.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void Model::setTransform(vec3 scale){
    glm_scale(this->modelMatrix, scale);
}

void Model_Scale(Model* M,float *scale){
    M->setTransform(scale);
}

mat4* Model::getTransform(){
    return &this->modelMatrix;
}

mat4* Model_Get_Transform(Model *M){
    return M->getTransform();
}