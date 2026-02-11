#include "shader.h"
#include "glad/glad.h"
#include "util.h"

void RMIInitShader(RMI_Shader *shader)
{
    // Vertex Shader
    unsigned int vShader;
    vShader = RMIUtilCreateFullShader(GL_VERTEX_SHADER,"vertexShader.glsl");

    // Fragment Shader
    unsigned int fShader;
    fShader = RMIUtilCreateFullShader(GL_FRAGMENT_SHADER,"fragmentShader.glsl");

    shader->program = glCreateProgram();

    glAttachShader(shader->program,vShader);
    glAttachShader(shader->program,fShader);
    glLinkProgram(shader->program); // compile shader

    RMIUniformInt(shader,"house",0); // Set house to GL_TEXTURE0;
    
    glDeleteShader(vShader);
    glDeleteShader(fShader);  
}

void RMIUniformInt(RMI_Shader *shader, const char* uniform, int x)
{
    glUniform1i(glGetUniformLocation(shader->program,uniform),x);
}

void RMIUnifromFloat(RMI_Shader *shader, const char *uniform, float f)
{
    glUniform1f(glGetUniformLocation(shader->program,uniform),f);
}

void RMIUnifromMat4f(RMI_Shader *shader, const char *uniform, mat4 m4)
{
    glUniformMatrix4fv(glGetUniformLocation(shader->program,uniform),1,GL_FALSE,(const float*)m4);
}