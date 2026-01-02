#pragma once

#include <nex.hpp>
using namespace NEX::Core;
using namespace NEX::GL;

#include <memory>

namespace Game::Objects::Office
{
    struct CallHandler
    {
        GLuint vbo;
        std::shared_ptr<Audio> a_call;
        std::shared_ptr<Texture> t_mute_call;

        CallHandler();
        ~CallHandler();

        void draw(void);
    };
}; // namespace Game::Objects::Office
