#include "night/call.hpp"

using namespace Game::Objects::Night;

CallHandler::CallHandler()
{
    this->a_call = AssetManager::get<Audio>("a_night_call");
    if (this->a_call != nullptr)
        this->a_call->play_track();

    this->t_mute_call = AssetManager::get<Texture>("t_mute_call");
}

CallHandler::~CallHandler() {}

void CallHandler::draw(void) {}