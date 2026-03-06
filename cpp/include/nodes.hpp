#pragma once
#include <vector>
#include "obj.hpp"
#include "../../cglm/include/cglm/cglm.h"

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
    unsigned int VAO, VBO, EBO;

    RMI_Obj* obj;
    mat4 modelMatrix = {
        {1.0f,0.0f,0.0f,0.0f},
        {0.0f,1.0f,0.0f,0.0f},
        {0.0f,0.0f,1.0f,0.0f},
        {0.0f,0.0f,0.0f,1.0f}
    };

    Model(const char* filename);

    virtual void Activate() override;

    void setTransform(vec3 scale);

    mat4* getTransform();

    ~Model();
};