#pragma once

#include <vector>
#include <memory>

namespace Core
{
    struct IState
    {
        virtual ~IState() = default;
        virtual void draw() = 0;
        virtual void update(double dt) = 0;
    };
    
    struct StateManager
    {
        void draw();
        void update(double dt);

        std::vector<std::shared_ptr<IState>> states;
    };
};