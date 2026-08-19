#include "RMI/rmi.h"
#include "glad/gl.h"
#include "globals.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

RMI_Result RMI_Init(Uint16 x, Uint16 y, void(*event)(SDL_Event* event), void(*update), void(*draw)){
    SDL_SetAppMetadata("Example HUMAN READABLE NAME", "1.0", "com.example.CATEGORY-NAME");
    if(!SDL_Init(SDL_INIT_VIDEO)) return RMI_RESULT_FAILURE;

    g_globals.width = x;
    g_globals.height = y;

    g_globals.eventHandler = event;
    g_globals.updateHandler = update;
    g_globals.drawHandler = draw;

    SDL_DisplayID dispID = SDL_GetPrimaryDisplay();
    const SDL_DisplayMode* dispMode = SDL_GetCurrentDisplayMode(dispID);

    if(!dispMode) {
        SDL_Log("%s\n",SDL_GetError());
        return RMI_RESULT_FAILURE;
    }

    g_globals.framePace = 1.0f / dispMode->refresh_rate;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    g_globals.window = SDL_CreateWindow("Cool Window", x, y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(!g_globals.window){
        return RMI_RESULT_FAILURE;
    }

    SDL_GLContext context;
    context = SDL_GL_CreateContext(g_globals.window);
    SDL_GL_MakeCurrent(g_globals.window, context);
    gladLoadGL((SDL_GL_GetProcAddress));

    return RMI_RESULT_SUCCESS;
}

void RMI_Deinit(){
    g_globals.running = false;

    if (g_globals.window) {
        SDL_GLContext context = SDL_GL_GetCurrentContext();
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(g_globals.window);
    }

    SDL_Quit();
};