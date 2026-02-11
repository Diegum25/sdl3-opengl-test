#include "sceneMatrix.h"
#include <cglm/cglm.h>

void RMIInitSceneMatrix(RMI_SceneMatrix * matrix, float sceneWidth, float sceneHeight)
{
    RMI_SceneMatrix newMatrix = {{
        {1.0f,0.0f,0.0f,0.0f},
        {0.0f,1.0f,0.0f,0.0f},
        {0.0f,0.0f,1.0f,0.0f},
        {0.0f,0.0f,0.0f,1.0f}
    },{
        {1.0f,0.0f,0.0f,0.0f},
        {0.0f,1.0f,0.0f,0.0f},
        {0.0f,0.0f,1.0f,0.0f},
        {0.0f,0.0f,0.0f,1.0f}
    },{
        {1.0f,0.0f,0.0f,0.0f},
        {0.0f,1.0f,0.0f,0.0f},
        {0.0f,0.0f,1.0f,0.0f},
        {0.0f,0.0f,0.0f,1.0f}
    }};

    *matrix = newMatrix;

    // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    vec3 axis = {1.0f, 0.0f, 0.0f};
    glm_rotate(matrix->model,glm_rad(-55.0f),axis);
    // view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    vec3 axis2 = {0.0f, 0.0f, -3.0f};
    glm_translate(matrix->view,axis2);
    // projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm_perspective(glm_rad(45.0f),sceneWidth / sceneHeight, 0.1f,100.0f, matrix->projection);

    glm_mat4_print(matrix->projection,stdout);
}