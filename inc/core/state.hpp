#pragma once

#include <vector>
#include <memory>

namespace Core
{
    struct IState
    {
        virtual ~IState() = default;
        virtual void draw() = 0;
        virtual void update() = 0;
    };
    
    struct StateManager
    {
        void draw();
        void update();

        std::vector<std::shared_ptr<IState>> states;
    };
};