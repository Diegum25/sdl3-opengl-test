#include "sceneMatrix.hpp"
#include <cglm/cglm.h>

sceneMatrix::sceneMatrix(float sceneWidth, float sceneHeight)
{
    // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    vec3 axis = {1.0f, 0.0f, 0.0f};
    glm_rotate(this->model,glm_rad(-55.0f),axis);
    // view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    vec3 axis2 = {0.0f, 0.0f, -3.0f};
    glm_translate(this->view,axis2);
    // projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm_perspective(glm_rad(45.0f),sceneWidth / sceneHeight, 0.1f,100.0f, this->projection);

    glm_mat4_print(this->projection,stdout);
}