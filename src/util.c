#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include "util.h"

#define RMI_DEBUG

GLuint createFullShader(GLenum type, char* fileName){
    GLuint shaderID;
    int fileSize;
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

    contents = SDL_malloc(fileSize + 1);

    size_t size = fread(contents,1,fileSize,stream); // ?
    contents[size]=0; // Add terminating zero.

    fclose(stream);
    glShaderSource(shaderID, 1, &contents, NULL);
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

bool checkShader(unsigned int shader){
    int success;
    char infolog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success) return true;

    glGetShaderInfoLog(shader, 512, NULL, infolog);
    SDL_Log("Shader is NOT ok %s", infolog);
    return false;
}