#ifdef RMI_MAIN
#ifndef RMI_MAIN_INCLUDED
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>

// SDL ALSO COMES WITH STB_IMAGE BUT IDK HOW TO USE IT
#define STB_IMAGE_IMPLEMENTATION // DONT PUT THIS ANYWHERE ELSE
#include "stb_image.h"

#include "sceneMatrix.h"
#include "shader.h"
#include "camera.h"
#include "scene.h"
#include "test.h"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static void* RMIAppState = NULL; // sdl does this the same way: https://github.com/libsdl-org/SDL/blob/main/src/main/SDL_main_callbacks.c

RMI_Scene scene;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    //glm_lookat(scene.camera.position,scene.camera.direction,scene.camera.upAxis,scene.matrix.view);

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

    window = SDL_CreateWindow("SDL3-OPENGL-TEST", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    if (!window) {
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // OpenGL setup the graphics context
    SDL_GLContext context; // ?
    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    // Setup our function pointers
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress); // weird thing <- ****** ai wrote this shit


    *appstate = malloc(sizeof(int));
    **(int**)appstate = 1;

    SDL_Log("hi the SDL appstate points to %d\n",**(int**)appstate);

    // stuff
    RMIInitScene(&scene,window);

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //glEnable(GL_CULL_FACE); // Face normals are currently ass

    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    RMI_Init(&RMIAppState);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT /* || event->type == SDL_EVENT_KEY_DOWN */){
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    if (event->type == SDL_EVENT_MOUSE_WHEEL){
        /* SDL_Log("change X:%f\n",event->wheel.x);
        SDL_Log("change Y:%f\n",event->wheel.y); */
        scene.camera.fov += event->wheel.y;
    }
    if (event->type == SDL_EVENT_MOUSE_MOTION){
        float changeX = event->motion.xrel * 0.15f;
        float changeY = -event->motion.yrel * 0.15f;
        scene.camera.yaw += changeX;

        //SDL_Log("yaw: %f\n",scene.camera.yaw);

        scene.camera.pitch = glm_clamp(scene.camera.pitch + changeY,-89.0f,89.0f);

        scene.camera.front[0] = SDL_cos(glm_rad(scene.camera.yaw)) * SDL_cos(glm_rad(scene.camera.pitch));
        scene.camera.front[1] = SDL_sin(glm_rad(scene.camera.pitch));
        scene.camera.front[2] = SDL_sin(glm_rad(scene.camera.yaw)) * SDL_cos(glm_rad(scene.camera.pitch));
        glm_normalize(scene.camera.front);
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
        default:
            break;
        }
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    //printf("hi the appstate points to %d\n",*(int*)appstate);
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

    RMICameraFlight(&scene.camera,moveDir);

    int x,y;
    SDL_GetWindowSizeInPixels(window,&x,&y);

    glm_perspective(glm_rad(scene.camera.fov),(float)x / (float)y, 0.1f,100.0f, scene.matrix.projection);
    glm_lookat(scene.camera.position,scene.camera.view,scene.camera.up,scene.matrix.view);

    glViewport(0,0,x,y);
    glClearColor(0.1f,0.1f,0.1f,1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    RMI_Update(RMIAppState);

    SDL_GL_SwapWindow(window);
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    free(appstate);
}
#define RMI_MAIN_INCLUDED
#endif
#endif