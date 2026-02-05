#include "util.hpp"

#define RMI_DEBUG

bool checkShader(unsigned int shader){
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success) return true;

    char infolog[512];

    glGetShaderInfoLog(shader, 512, NULL, infolog);
    SDL_Log("Shader is NOT ok %s", infolog);
    return false;
}

unsigned int createFullShader(GLenum type, const char* fileName){
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

    #ifdef RMI_DEBUG
        int  success;
        char infoLog[512];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
            SDL_Log("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s",infoLog);
            glDeleteShader(shaderID);
            return 0;
        }
    #endif

    SDL_free(contents);

    if (checkShader(shaderID)) return shaderID;

    // if fail
    glDeleteShader(shaderID);

    return 0;
}