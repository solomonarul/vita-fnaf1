#include "core/delta.hpp"

using namespace Core;

#include <SDL3/SDL.h>

Delta::Delta() : last(SDL_GetPerformanceCounter()) { }

double Delta::tick()
{
    uint64_t now = SDL_GetPerformanceCounter();
    double dt = double(now - last) / float(SDL_GetPerformanceFrequency());
    last = now;
    return dt;
}