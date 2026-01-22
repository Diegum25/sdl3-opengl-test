#include <SDL3/SDL.h>
#include <glad/glad.h>
#include "util.h"
bool checkShader(unsigned int shader){
    int success;
    char infolog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success) return true;

    glGetShaderInfoLog(shader, 512, NULL, infolog);
    SDL_Log("Shader is NOT ok %s", infolog);
    return false;
}