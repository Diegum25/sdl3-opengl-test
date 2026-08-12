#include "RMI/rmi.h"
#include "glad/gl.h"
#include "globals.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

RMI_Result RMI_Init(Uint16 x, Uint16 y, void(*event)(SDL_Event* event), void(*update), void(*draw)){
    volatile RMI_Globals* globals = RMI_GetGlobals();

    RMI_R_SetupGlobals(globals);
    RMI_W_SetupGlobals(globals);

    SDL_SetAppMetadata("Example HUMAN READABLE NAME", "1.0", "com.example.CATEGORY-NAME");
    if(!SDL_Init(SDL_INIT_VIDEO)) return RMI_RESULT_FAILURE;

    globals->width = x;
    globals->height = y;

    globals->eventHandler = event;
    globals->updateHandler = update;
    globals->drawHandler = draw;

    SDL_DisplayID dispID = SDL_GetPrimaryDisplay();
    const SDL_DisplayMode* dispMode = SDL_GetCurrentDisplayMode(dispID);

    if(!dispMode) {
        SDL_Log("%s\n",SDL_GetError());
        return RMI_RESULT_FAILURE;
    }

    globals->framePace = 1.0f / dispMode->refresh_rate;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    globals->window = SDL_CreateWindow("Cool Window", x, y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(!globals->window){
        return RMI_RESULT_FAILURE;
    }

    SDL_GLContext context;
    context = SDL_GL_CreateContext(globals->window);
    SDL_GL_MakeCurrent(globals->window, context);
    gladLoadGL((SDL_GL_GetProcAddress));

    return RMI_RESULT_SUCCESS;
}

void RMI_Deinit(){
    volatile RMI_Globals* glabas = RMI_GetGlobals();
    glabas->running = false;

    if (glabas->window) {
        SDL_GLContext context = SDL_GL_GetCurrentContext();
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(glabas->window);
    }

    SDL_Quit();
};