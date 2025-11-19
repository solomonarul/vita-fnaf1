#include "core/state.hpp"

using namespace Core;

void StateManager::draw(int w, int h)
{
    for(auto& state : states)
        state->draw(w, h);
}

void StateManager::update(double dt)
{
    for(auto& state : states)
        state->update(dt);
}
