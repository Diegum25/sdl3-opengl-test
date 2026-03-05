#pragma once
#include <vector>
#include "obj.h"
#include "../../glad/include/glad/glad.h"
#include <stdlib.h> // ?

// Virtually all fields are private anyways. 
// And there is no point to marking stuff as private.

class TestClass{
    private:
    int coolInt = 1;
    public:
    int getCoolInt();
};

class Node{
    public:
    std::vector<Node*> children;
    void AddChild(Node* newChild);
    virtual void Activate(){};
};

class PolymorphismInCWTF : public Node{
    public:
    const char* text;
    void (*SDL_Log)(const char *fmt, ...);
    PolymorphismInCWTF(void (*SDL_Log)(const char *fmt, ...),const char* text);
    virtual void Activate() override;
};

class Model : public Node{
    public:
    RMI_obj obj;

    unsigned int VAO, VBO, EBO;

    Model(void(*RMILoadOBJ)(RMI_obj*,const char*),const char* filename);

    ~Model();
};