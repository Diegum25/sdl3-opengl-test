#include "shader.h"
#include "glad/glad.h"
#include "util.h"

void RMIInitShader(RMI_Shader *shader, const char* verShader, const char* fragShader, RMI_SceneMatrix* matrix)
{
    // Vertex Shader
    unsigned int vShader;
    vShader = RMIUtilCreateFullShader(GL_VERTEX_SHADER,verShader);

    // Fragment Shader
    unsigned int fShader;
    fShader = RMIUtilCreateFullShader(GL_FRAGMENT_SHADER,fragShader);

    shader->program = glCreateProgram();

    glAttachShader(shader->program,vShader);
    glAttachShader(shader->program,fShader);
    glLinkProgram(shader->program); // compile shader

    RMIUniformInt(shader,"house",0); // Set house to GL_TEXTURE0;
    
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    if (matrix){
        glUseProgram(shader->program);
        RMIUniformMat4f(shader,"model",matrix->model);
        RMIUniformMat4f(shader,"view",matrix->view);
        RMIUniformMat4f(shader,"projection",matrix->projection);
    }
}

void RMIUniformInt(RMI_Shader *shader, const char* uniform, int x) // we dont need to be bound
{
    glUniform1i(glGetUniformLocation(shader->program,uniform),x);
}

void RMIUniformFloat(RMI_Shader *shader, const char *uniform, float f) // we dont need to be bound
{
    glUniform1f(glGetUniformLocation(shader->program,uniform),f);
}

void RMIUniformMat4f(RMI_Shader *shader, const char *uniform, mat4 m4) // we dont need to be bound
{
    glUniformMatrix4fv(glGetUniformLocation(shader->program,uniform),1,GL_FALSE,(const float*)m4);
}

void RMIUniformVec3(RMI_Shader *shader, const char *unifrom, vec3 v3)
{
    glUniform3fv(glGetUniformLocation(shader->program,unifrom),1,(const float*)v3);
}
