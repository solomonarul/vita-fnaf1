#pragma once

#include "../core/asset.hpp"

#include <SDL3/SDL_opengles2.h>

#include <string>

namespace GL
{
    struct Texture : public Core::Asset
    {
        GLuint id;
        int w, h, ch;
        void* data;
        
        void bind();
        void activate(GLenum);
        Texture(std::string);
        ~Texture();
    };
};