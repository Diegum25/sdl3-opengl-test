#include "obj.h"
#include "SDL3/SDL.h"

obj_data getObjData(const char* objPath){
    obj_data data = {.fileName = objPath, .quads = 1, .tris = 1, .verts = SDL_malloc(sizeof(float))};
    return data;
}