#include "util.h"

#define RMI_DEBUG

bool RMIUtilCheckShader(unsigned int shader){
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success) return true;
    #ifdef RMI_DEBUG
        char infolog[512];

        glGetShaderInfoLog(shader, 512, NULL, infolog);
        SDL_Log("Shader is NOT ok %s", infolog);
    #endif
    return false;
}

unsigned int RMIUtilCreateFullShader(GLenum type, const char* fileName){
    unsigned int shaderID;
    size_t fileSize;
    char* contents;
    shaderID = glCreateShader(type);

    // https://stackoverflow.com/questions/11793689/read-the-entire-contents-of-a-file-to-c-char-including-new-lines
    // bro
    
    FILE* stream = fopen(fileName,"rb");

    #ifdef RMI_DEBUG
        if (stream == NULL){
            SDL_Log("Couldnt read file: %s",fileName);
            glDeleteShader(shaderID);
            return 0;
        }
    #endif

    fseek(stream, 0L, SEEK_END);
    fileSize = ftell(stream);
    fseek(stream, 0L, SEEK_SET);

    contents = (char*)SDL_malloc(fileSize + 1);

    size_t size = fread(contents,1,fileSize,stream);
    contents[size]=0; // Add terminating zero.

    const char* source = contents;

    fclose(stream);
    glShaderSource(shaderID, 1, &source, NULL);
    glCompileShader(shaderID);

    SDL_free(contents);

    if (RMIUtilCheckShader(shaderID)) return shaderID;

    // if fail
    glDeleteShader(shaderID);

    return 0;
}