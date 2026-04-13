#ifndef RMI_SHADER_INTERNAL_H
#define RMI_SHADER_INTERNAL_H

#include "cglm/cglm.h"
#include "sceneMatrix.h"

/* 
    What I want:
        Find occurances of unifroms and vertex data and automate that shit somehow
            but i guess that will be on a different struct
 */

typedef struct{ // MAKE SURE TO ONLY INIT AFTER GLAD GETS SET UP!
    unsigned int program;
} RMI_Shader;

void RMIInitShader(RMI_Shader* shader, const char* vShader, const char* fShader, RMI_SceneMatrix* matrix); // matrix can be NULL if your shader doesnt have: (model, view & projection uniforms)

void RMIUniformInt(RMI_Shader* shader, const char * uniform, int i);
void RMIUniformFloat(RMI_Shader* shader, const char * uniform, float f);
void RMIUniformMat4f(RMI_Shader* shader, const char * uniform, mat4 m4);
void RMIUniformVec3(RMI_Shader* shader, const char* unifrom, vec3 v3);
#endif