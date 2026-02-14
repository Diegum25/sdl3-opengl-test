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

/*
 * This example code $WHAT_IT_DOES.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */



/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;

/* This function runs once at startup. */


RMI_Shader regularShader;
RMI_Texture texture;

unsigned int VBO, VAO;

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

RMI_Camera camera;
RMI_SceneMatrix matrix;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{

    time = SDL_GetTicks();

    RMIInitCamera(&camera);
    RMIInitSceneMatrix(&matrix,width,height);
    //glm_lookat(camera.position,camera.direction,camera.upAxis,matrix.view);

    stbi_set_flip_vertically_on_load_thread(true);

    SDL_SetAppMetadata("Example HUMAN READABLE NAME", "1.0", "com.example.CATEGORY-NAME");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
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

    // --- Shaders & program ---

    RMIInitShader(&regularShader);

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


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //glEnable(GL_CULL_FACE); // Face normals are currently ass

    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    glUseProgram(regularShader.program);
    RMIUnifromMat4f(&regularShader,"model",matrix.model);
    RMIUnifromMat4f(&regularShader,"view",matrix.view);
    RMIUnifromMat4f(&regularShader,"projection",matrix.projection);

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
            glm_perspective(glm_rad(45.0f),(float)x / (float)y, 0.1f,100.0f, matrix.projection);
            if (regularShader.program){
                glUseProgram(regularShader.program);
                RMIUnifromMat4f(&regularShader,"projection",matrix.projection);
            }
            //SDL_Log("New size:\nx=%d\ny=%d",width,height);
        }
    }
    if (event->type == SDL_EVENT_MOUSE_MOTION){
        /* float change = event->motion.xrel;
        vec3 axis = {0.0f,1.0f,0.0f};
        glm_rotate(matrix.view,glm_rad(change),axis); */
    }
    if (event->type == SDL_EVENT_KEY_DOWN){
        switch (event->key.key)
        {
        case SDLK_ESCAPE:
            return SDL_APP_SUCCESS;
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

    if (key_states[SDL_SCANCODE_W]){
        camera.position[2] -= 0.1f;
    }
    if (key_states[SDL_SCANCODE_S]){
        camera.position[2] += 0.1f;
    }
    if (key_states[SDL_SCANCODE_A]){
        camera.position[0] -= 0.1f;
    }
    if (key_states[SDL_SCANCODE_D]){
        camera.position[0] += 0.1f;
    }

    glViewport(0,0,width,height);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(regularShader.program);
    glm_lookat(camera.position,camera.direction,camera.upAxis,matrix.view);
    RMIUnifromMat4f(&regularShader,"view",matrix.view);
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

        RMIUnifromMat4f(&regularShader,"model",model);

        glDrawArrays(GL_TRIANGLES, 0 , 36);
    }
    glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}