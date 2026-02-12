#include "texture.h"
#include "glad/glad.h"
#include "stb_image.h"
#include <SDL3/SDL.h>

void RMIInitTexture(RMI_Texture * texture, const char * fileName)
{
    int imgWidth, imgHeight, imgChannels;
    unsigned char* imgData = stbi_load(fileName,&imgWidth,&imgHeight,&imgChannels,0);

    if (!imgData){
        SDL_Log("Could not load \"%s\".\nCheck that out bro.",fileName);
        return;
    }

    glGenTextures(1,&texture->ID);

    glBindTexture(GL_TEXTURE_2D,texture->ID);

    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imgData);
}