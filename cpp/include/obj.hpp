#pragma once
#include <vector>

class RMI_Obj{
    public:
    std::vector<float> verts;
    std::vector<unsigned int> indexes;

    RMI_Obj(const char* filename);
    ~RMI_Obj();
};