#include "core/inputmanager.hpp"

using namespace Core;

void InputManager::handle_event(SDL_Event& event)
{
    switch(event.type)
    {
    case SDL_EVENT_MOUSE_MOTION:
        InputManager::self().m_data.x = event.pmotion.x;
        InputManager::self().m_data.y = event.pmotion.y;
        break;
    }
}

InputManager::MouseData InputManager::get_mouse_data()
{
    return InputManager::self().m_data;
}

InputManager& InputManager::self()
{
    static InputManager self;
    return self;
}