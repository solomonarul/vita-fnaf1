#pragma once

#include <nex.hpp>
using namespace NEX::Core;
using namespace NEX::GL;

#include <memory>

namespace Game::Objects::Night
{
    struct CallHandler
    {
        std::shared_ptr<Audio> a_call;
        std::shared_ptr<Texture> t_mute_call;

        CallHandler();
        ~CallHandler();

        void draw();
    };
}; // namespace Game::Objects::Night
