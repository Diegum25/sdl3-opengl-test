#pragma once

#include "cglm/cglm.h"

/* 
    What I want:
        Find occurances of unifroms and vertex data and automate that shit somehow
            but i guess that will be on a different struct
 */

typedef struct{ // MAKE SURE TO ONLY INIT AFTER GLAD GETS SET UP!
    unsigned int program;
} RMI_Shader;

void RMIInitShader(RMI_Shader* shader);

void RMIUniformInt(RMI_Shader* shader, const char * uniform, int i);
void RMIUnifromFloat(RMI_Shader* shader, const char * uniform, float f);
void RMIUnifromMat4f(RMI_Shader* shader, const char * uniform, mat4 m4);