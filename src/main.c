#include "node_base.h"
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>

// SDL ALSO COMES WITH STB_IMAGE BUT IDK HOW TO USE IT
#define STB_IMAGE_IMPLEMENTATION // DONT PUT THIS ANYWHERE ELSE
#include "stb_image.h"

#include "RMI/RMI_callbacks.h"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static void* RMIAppState = NULL; // sdl does this the same way: https://github.com/libsdl-org/SDL/blob/main/src/main/SDL_main_callbacks.c

static RMI_Node* root;

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

    }
    if (event->type == SDL_EVENT_MOUSE_MOTION){

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
    int x,y;
    SDL_GetWindowSizeInPixels(window,&x,&y);

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
    RMI_End(RMIAppState);
}