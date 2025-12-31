#include "night/call.hpp"

using namespace Game::Objects::Night;

CallHandler::CallHandler() {
    this->a_call = AssetManager::get<Audio>("a_night_call");
    if(this->a_call != nullptr)
        MIX_PlayTrack(this->a_call->track, 0);
}

CallHandler::~CallHandler() {}
