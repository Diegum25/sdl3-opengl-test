#pragma once

/* 
    What I want:
        Find occurances of unifroms and vertex data and automate that shit
        To be able to send data to uniforms easily with self referencing funcitions
            Apparently this can be done with macros
 */

typedef struct{
    unsigned int program;
} shader;

void initShader(shader* shader);