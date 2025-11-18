#pragma once

#include <SDL3/SDL_opengles2.h>

#include <string>

namespace GL
{
    struct Texture
    {
        GLuint id;
        int w, h, ch;
        uint8_t* data;
        
        void bind();
        void activate(GLenum);
        Texture(std::string);
        ~Texture();
    };
};