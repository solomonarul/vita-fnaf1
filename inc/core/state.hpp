#pragma once

#include <SDL3/SDL_events.h>

#include <vector>
#include <memory>

namespace Core
{
    struct StateManager;
    
    struct IState
    {
        IState(StateManager& sm) : state_manager(sm) { }
        
        StateManager& state_manager;
        virtual ~IState() = default;
        virtual void draw(int, int) = 0;
        virtual void update(double) = 0;
        virtual void event(SDL_Event&) = 0;
    };
    
    struct StateManager
    {
        void draw(int, int);
        void update(double);
        void send(SDL_Event&);

        std::vector<std::unique_ptr<IState>> states;
    };
};