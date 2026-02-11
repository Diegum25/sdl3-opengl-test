#pragma once

#include "cglm/cglm.h"

/* 
    What I want:
        Find occurances of unifroms and vertex data and automate that shit somehow
            but i guess that will be on a different struct
 */

typedef struct{ // MAKE SURE TO ONLY INIT AFTER GLAD GETS SET UP!
    unsigned int program;
} shader;

void initShader(shader* shader);

void sendInt(shader* shader, const char * uniform, int i);
void sendFloat(shader* shader, const char * uniform, float f);
void sendMat4f(shader* shader, const char * uniform, mat4 m4);