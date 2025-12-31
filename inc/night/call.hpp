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
        CallHandler();
        ~CallHandler();
    };
}; // namespace Game::Objects::Night
