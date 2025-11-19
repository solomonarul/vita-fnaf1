#pragma once

#include <vector>
#include <memory>

namespace Core
{
    struct IState
    {
        virtual ~IState() = default;
        virtual void draw(int w, int h) = 0;
        virtual void update(double dt) = 0;
    };
    
    struct StateManager
    {
        void draw(int w, int h);
        void update(double dt);

        std::vector<std::unique_ptr<IState>> states;
    };
};