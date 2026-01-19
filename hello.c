/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>

int main(int argc, char* argv[]){

    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=NULL;

    // Initialize the video subsystem.
    // If it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_Log("SDL could not be initialized: ");
    }else{
        SDL_Log("SDL video system is ready to go\n");
    }
    // Before we create our window, specify OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C SDL3 Window",
            640,
            480,
            SDL_WINDOW_OPENGL);

    // OpenGL setup the graphics context
    SDL_GLContext context;
    context = SDL_GL_CreateContext(window);

    // Setup our function pointers
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    // Infinite loop for our application
    bool gameIsRunning = true;
    while(gameIsRunning){
        glViewport(0,0,640,480);

        SDL_Event event;
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED){
                SDL_Log("Close window event\n");
                gameIsRunning= false;
            }
            if(event.type == SDL_EVENT_MOUSE_MOTION){
                SDL_Log("Mpuse has been moved\n");
            }
            if(event.type == SDL_EVENT_KEY_DOWN){
                SDL_Log("a key has been pressed\n");
                if(event.key.key == SDLK_0){
                    SDL_Log("0 was pressed\n");
                }else{
                    SDL_Log("0 was not pressed\n");
                }
            }
            // Retrieve the state of all of the keys
            // Then we can query the scan code of one or more
            // keys at a time
            const Uint8* state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_RIGHT]){
                SDL_Log("right arrow key is pressed\n");
            }
        }

        glClearColor(1.0f,0.0f,0.0f,1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    // our program.
    SDL_Quit();
    return 0;
}