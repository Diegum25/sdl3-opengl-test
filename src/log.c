#include "RMI/rmi.h"
#include "SDL3/SDL.h"

// shameless SDL_Log wrap

void RMI_Log(SDL_PRINTF_FORMAT_STRING const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, fmt, ap);
    va_end(ap);
}