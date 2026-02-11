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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "cglm/cglm.h"

#include "sceneMatrix.h"
#include "shader.h"

/*
 * This example code $WHAT_IT_DOES.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */



/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;

/* This function runs once at startup. */


shader regularShader;

unsigned int VBO, VAO, EBO, texture;

int width = 640;
int height = 480;

mat4 transform = {
    {1.0f,0.0f,0.0f,0.0f},
    {0.0f,1.0f,0.0f,0.0f},
    {0.0f,0.0f,1.0f,0.0f},
    {0.0f,0.0f,0.0f,1.0f}
};

sceneMatrix matrix;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    initSceneMatrix(&matrix,width,height);

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

    initShader(&regularShader);

    // --- Vertex data and buffers ---

    float verts[] = {
    //Verts             //Texture
    0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
    };

    unsigned int indexes[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };


    // this has nothing to do with the VAO and can be used anywhere
    // also need to put all this shit on a funcion
    glGenTextures(1,&texture);

    glBindTexture(GL_TEXTURE_2D,texture);

    // ?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    int imgWidth, imgHeight, imgChannels;
    unsigned char* imgData = stbi_load("house.bmp",&imgWidth,&imgHeight,&imgChannels,0);
    glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes),indexes,GL_STATIC_DRAW);

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

    /* glEnable(GL_CULL_FACE);

    glCullFace(GL_FRONT); */

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
            //SDL_Log("New size:\nx=%d\ny=%d",width,height);
        }
    }
    if (event->type == SDL_EVENT_MOUSE_MOTION){
        float change = event->motion.xrel;
        vec3 axis = {0.0f,1.0f,0.0f};
        glm_rotate(matrix.view,glm_rad(change),axis);
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    glViewport(0,0,width,height);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0); // SET HOUSE'S UNIT
    glBindTexture(GL_TEXTURE_2D,texture);

    // I also dont know why these arent presisting
    sendMat4f(&regularShader,"transform",transform);
    sendMat4f(&regularShader,"model",matrix.model);
    sendMat4f(&regularShader,"view",matrix.view);
    sendMat4f(&regularShader,"projection",matrix.projection);
    
    glUseProgram(regularShader.program);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
