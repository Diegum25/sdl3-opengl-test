#ifndef RMI_TEXTURE_INTERNAL_H
#define RMI_TEXTURE_INTERNAL_H
#include "glad/glad.h"

/* 
    What i want
        Make texture creation (with weird properties) easier
        Find occurances of unifroms and vertex data and automate that shit somehow
            but i guess that will be on a different struct
 */

typedef struct{
    unsigned int ID;
} RMI_Texture;

/* typedef struct
{

} RMI_TextureParameters; */

void RMIInitTexture(RMI_Texture*,const char *);
#endif