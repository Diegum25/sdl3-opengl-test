/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>
#include "util.h"

#define STB_IMAGE_IMPLEMENTATION // DONT PUT THIS ANYWHERE ELSE
#include "stb_image.h"

#include "cglm/cglm.h"

#include "sceneMatrix.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "obj.h"

/*
 * This example code $WHAT_IT_DOES.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */



/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;

/* This function runs once at startup. */


RMI_Shader regularShader, anotherShader;
RMI_Texture texture;

unsigned int VBO, VAO, VAO2, VBO3, VAO3, EBO3;

int width = 640;
int height = 480;

uint64_t time;

vec3 cubePositions[] = {
    { 0.0f,  0.0f,   0.0f},
    { 2.0f,  5.0f, -15.0f},
    {-1.5f, -2.2f,  -2.5f},
    {-3.8f, -2.0f, -12.3f},
    { 2.4f, -0.4f,  -3.5f},
    {-1.7f,  3.0f,  -7.5f},
    { 1.3f, -2.0f,  -2.5f},
    { 1.5f,  2.0f,  -2.5f},
    { 1.5f,  0.2f,  -1.5f},
    {-1.3f,  1.0f,  -1.5f},
    { 2.0f,  1.5f,  -6.0f},
    {-2.0f, -1.5f,  -6.0f},
    { 0.5f,  2.5f,  -4.0f},
    {-0.5f, -2.5f,  -4.0f},
    { 3.0f,  0.0f,  -8.0f}
};

vec3 lightPosition = {0.0f,0.0f,-10.0f};
vec3 lightColour = {1.0f,1.0f,1.0f};

RMI_Camera camera;
RMI_SceneMatrix matrix;

RMI_obj objCube;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    RMIInitCamera(&camera);
    RMIInitSceneMatrix(&matrix,width,height);
    //glm_lookat(camera.position,camera.direction,camera.upAxis,matrix.view);

    stbi_set_flip_vertically_on_load_thread(true);

    SDL_SetAppMetadata("Example HUMAN READABLE NAME", "1.0", "com.example.CATEGORY-NAME");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        //SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Before we create our window, specify OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    window = SDL_CreateWindow("SDL3-OPENGL-TEST", width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    if (!window) {
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // OpenGL setup the graphics context
    SDL_GLContext context;
    context = SDL_GL_CreateContext(window);

    // Setup our function pointers
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress); // weird thing <- ****** ai wrote this shit

    time = SDL_GetTicks();

    // --- Shaders & program ---

    RMIInitShader(&regularShader,"testing/vertexShader.glsl","testing/fragmentShader.glsl",&matrix);
    RMIInitShader(&anotherShader,"testing/simpleVShader.glsl","testing/simpleFShader.glsl",&matrix);

    // --- Vertex data and buffers ---

    float verts[] = {
        // Position         // Texture
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    RMILoadOBJ(&objCube,"testing/teapot.obj");
    //printf("%ld\n",sizeof(float)* objCube.vertsAmnt);

    // this has nothing to do with the VAO and can be used anywhere

    RMIInitTexture(&texture,"testing/house.bmp");

    // also need to put all this shit on a funcion
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    
    
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // end of sorts totally optional

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // location=0 from the shader
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); // location=1 from the shader

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0); // end of sorts totally optional

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); // end of sorts this all goes into the VAO. i believe

    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glGenVertexArrays(1,&VAO3);
    glGenBuffers(1,&VBO3);
    glGenBuffers(1,&EBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER,VBO3);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float) * objCube.vertsAmnt, objCube.verts,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * objCube.indexAmnt, objCube.indexes,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    free(objCube.verts);
    free(objCube.indexes);
    
    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //glEnable(GL_CULL_FACE); // Face normals are currently ass

    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT /* || event->type == SDL_EVENT_KEY_DOWN */){
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    if (event->type == SDL_EVENT_WINDOW_RESIZED){
        int x;
        int y;
        bool success = SDL_GetWindowSizeInPixels(window,&x,&y);
        if (success){
            width = x;
            height = y;
            //SDL_Log("New size:\nx=%d\ny=%d",width,height);
        }
    }
    if (event->type == SDL_EVENT_MOUSE_WHEEL){
        /* SDL_Log("change X:%f\n",event->wheel.x);
        SDL_Log("change Y:%f\n",event->wheel.y); */
        camera.fov += event->wheel.y;
        int x;
        int y;
        bool success = SDL_GetWindowSizeInPixels(window,&x,&y);
        if (success){
            width = x;
            height = y;
            //SDL_Log("New size:\nx=%d\ny=%d",width,height);
        }
    }
    if (event->type == SDL_EVENT_MOUSE_MOTION){
        float changeX = event->motion.xrel * 0.15f;
        float changeY = -event->motion.yrel * 0.15f;
        camera.yaw += changeX;

        //SDL_Log("yaw: %f\n",camera.yaw);

        camera.pitch = glm_clamp(camera.pitch + changeY,-89.0f,89.0f);

        camera.front[0] = SDL_cos(glm_rad(camera.yaw)) * SDL_cos(glm_rad(camera.pitch));
        camera.front[1] = SDL_sin(glm_rad(camera.pitch));
        camera.front[2] = SDL_sin(glm_rad(camera.yaw)) * SDL_cos(glm_rad(camera.pitch));
        glm_normalize(camera.front);
        //SDL_Log("yaw:%f\n",camera.yaw);
    }
    if (event->type == SDL_EVENT_KEY_DOWN){
        switch (event->key.key)
        {
        case SDLK_ESCAPE:
            return SDL_APP_SUCCESS;
            break;
        case SDLK_B:
            SDL_SetWindowRelativeMouseMode(window,true);
            break;
        case SDLK_V:
            SDL_SetWindowRelativeMouseMode(window,false);
            break;
        case SDLK_N:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case SDLK_M:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    
            break;
        case SDLK_DOWN:
            lightPosition[2] -= 1.0f;
            break;
        case SDLK_UP:
            lightPosition[2] += 1.0f;
            break;
        case SDLK_RIGHT:
            lightPosition[0] -= 1.0f;
            break;
        case SDLK_LEFT:
            lightPosition[0] += 1.0f;
            break;
        default:
            break;
        }
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    const bool* key_states = SDL_GetKeyboardState(NULL);
    const float speed = -0.1f;
    vec2 moveDir = {0.0f,0.0f};

    if (key_states[SDL_SCANCODE_W]){
        vec2 add = {0.0f,1.0f};
        glm_vec2_add(moveDir,add,moveDir);
    }
    if (key_states[SDL_SCANCODE_S]){
        vec2 add = {0.0f,-1.0f};
        glm_vec2_add(moveDir,add,moveDir);
    }
    if (key_states[SDL_SCANCODE_A]){
        vec2 add = {-1.0f,0.0f};
        glm_vec2_add(moveDir,add,moveDir);
    }
    if (key_states[SDL_SCANCODE_D]){
        vec2 add = {1.0f,0.0f};
        glm_vec2_add(moveDir,add,moveDir);
    }

    glm_vec2_normalize(moveDir); // emulate circular analog stick

    //  glm_vec2_print(moveDir,stdout);

    RMICameraFlight(&camera,moveDir);
    glm_perspective(glm_rad(camera.fov),(float)width / (float)height, 0.1f,100.0f, matrix.projection);
    glm_lookat(camera.position,camera.view,camera.up,matrix.view);

    //party time!
    /* lightColour [0] = (SDL_sin(SDL_GetTicks() / 128) + 1.0)/2.0;
    lightColour [1] = (SDL_cos(SDL_GetTicks() / 64) + 1.0)/2.0;
    lightColour [2] = (SDL_sin((SDL_GetTicks() + 20.0) / 128) + 1.0)/2.0; */

    glViewport(0,0,width,height);
    glClearColor(0.1f,0.1f,0.1f,1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(regularShader.program);

    RMIUniformMat4f(&regularShader,"projection",matrix.projection);
    RMIUniformMat4f(&regularShader,"view",matrix.view);
    glActiveTexture(GL_TEXTURE0); // SET HOUSE'S UNIT
    glBindTexture(GL_TEXTURE_2D,texture.ID);

    glBindVertexArray(VAO);
    for (int i = 0; i < 15; i++){
        mat4 model = {
            {1.0f,0.0f,0.0f,0.0f},
            {0.0f,1.0f,0.0f,0.0f},
            {0.0f,0.0f,1.0f,0.0f},
            {0.0f,0.0f,0.0f,1.0f}
        };

        glm_translate(model,cubePositions[i]);

        float angle = (20.0f * i) + (SDL_GetTicks() - time)/32;

        vec3 axis = {1.0f,0.3f,0.5f};
        glm_rotate(model,glm_rad(angle),axis);

        RMIUniformMat4f(&regularShader,"model",model);

        //distance to light
        const float falloff = 25.0f;
        float distance = glm_vec3_distance(lightPosition,cubePositions[i]);
        
        float lightAmount = glm_clamp((-distance/falloff) + 1.0f,0.0f,1.0f);

        RMIUniformFloat(&regularShader,"lightAmount",lightAmount);
        RMIUniformVec3(&regularShader,"lightColour",lightColour);


        glDrawArrays(GL_TRIANGLES, 0 , 36);
    }
    glUseProgram(anotherShader.program);
    mat4 model = {
        {1.0f,0.0f,0.0f,0.0f},
        {0.0f,1.0f,0.0f,0.0f},
        {0.0f,0.0f,1.0f,0.0f},
        {0.0f,0.0f,0.0f,1.0f}
    };
    glm_translate(model,lightPosition);
    RMIUniformMat4f(&anotherShader,"model",model);
    RMIUniformMat4f(&anotherShader,"projection",matrix.projection);
    RMIUniformMat4f(&anotherShader,"view",matrix.view);
    RMIUniformVec3(&anotherShader,"lightColor",lightColour);
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glUseProgram(anotherShader.program);
    mat4 model2 = {
        {1.0f,0.0f,0.0f,0.0f},
        {0.0f,1.0f,0.0f,0.0f},
        {0.0f,0.0f,1.0f,0.0f},
        {0.0f,0.0f,0.0f,1.0f}
    };
    vec3 scale = {0.025f,0.025f,0.025f};
    glm_scale(model2,scale);
    vec3 axis = {0.0f,1.0f,0.0f};
    glm_rotate(model2,SDL_GetTicks() / 128.0f,axis);
    RMIUniformMat4f(&anotherShader,"model",model2);
    RMIUniformMat4f(&anotherShader,"projection",matrix.projection);
    RMIUniformMat4f(&anotherShader,"view",matrix.view);
    glBindVertexArray(VAO3);
    glDrawElements(GL_TRIANGLES, objCube.indexAmnt,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}