#ifndef RMI_UNTIL_INTERNAL_H
#define RMI_UNTIL_INTERNAL_H

// old stuff

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include <cglm/cglm.h>

bool RMIUtilCheckShader(unsigned int shader);

unsigned int RMIUtilCreateFullShader(GLenum type, const char* fileName); // it already deletes the shader if it fails.
#endif