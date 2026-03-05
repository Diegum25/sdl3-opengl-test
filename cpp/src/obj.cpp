#include "obj.hpp"
#include <fstream>
#include <string.h> // strcmp my beloved

RMI_Obj::RMI_Obj(const char * filename){
    std::fstream file(filename, std::fstream::in);

    char type[3];

    while(!file.eof()){
        file >> std::ws;
        file.read(type,2);
        type[2] = '\0';
        if(strcmp(type,"v ") == 0){
            float x,y,z;
            file >> x >> y >> z;
            this->verts.push_back(x);
            this->verts.push_back(y);
            this->verts.push_back(z);
        }else if (strcmp(type,"f ") == 0)
        {
            unsigned int x,y,z;
            file >> x >> y >> z;
            this->indexes.push_back(x - 1);
            this->indexes.push_back(y - 1);
            this->indexes.push_back(z - 1);
        }
        file.ignore(64,'\n');
    };

    file.close();
}

RMI_Obj::~RMI_Obj(){
}