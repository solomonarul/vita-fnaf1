#pragma once

#include <SDL3/SDL.h>

namespace Core
{
    class Delta
    {
    public:
        Delta() : last(SDL_GetPerformanceCounter()) {}

        double tick()
        {
            uint64_t now = SDL_GetPerformanceCounter();
            double dt = double(now - last) / float(SDL_GetPerformanceFrequency());
            last = now;
            return dt;
        }

    private:
        uint64_t last;
    };
};

