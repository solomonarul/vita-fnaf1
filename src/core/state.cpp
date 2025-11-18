#include "core/state.hpp"

using namespace Core;

void StateManager::draw()
{
    for(auto& state : states)
        state->draw();
}

void StateManager::update(double dt)
{
    for(auto& state : states)
        state->update(dt);
}
