#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include "util.h"

GLuint createFullShader(GLenum type, char* fileName){
    GLuint shaderID;
    int fileSize;
    char* contents;
    shaderID = glCreateShader(type);

    // https://stackoverflow.com/questions/11793689/read-the-entire-contents-of-a-file-to-c-char-including-new-lines
    // bro
    
    FILE* stream = fopen(fileName,"rb");
    fseek(stream, 0L, SEEK_END);
    fileSize = ftell(stream);
    fseek(stream, 0L, SEEK_SET);

    contents = SDL_malloc(fileSize + 1);

    size_t size = fread(contents,1,fileSize,stream); // ?
    contents[size]=0; // Add terminating zero.

    fclose(stream);
    glShaderSource(shaderID, 1, &contents, NULL);
    glCompileShader(shaderID);

    SDL_free(contents);
    
    if (checkShader(shaderID)) return shaderID;
    
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