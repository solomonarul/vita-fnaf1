#include "core/delta.hpp"

#include "core/defines.hpp"

using namespace Core;

Delta::Delta() : last(SDL_GetPerformanceCounter()) { }

double Delta::tick()
{
    uint64_t now = SDL_GetPerformanceCounter();
    double dt = double(now - last) / float(SDL_GetPerformanceFrequency());
    last = now;
    return dt;
}