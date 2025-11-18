#include "core/state.hpp"

using namespace Core;

void StateManager::draw()
{
    for(auto& state : states)
        state->draw();
}

void StateManager::update()
{
    for(auto& state : states)
        state->update();
}
