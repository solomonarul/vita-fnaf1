#pragma once

#include "../core/asset.hpp"

#include <SDL3/SDL_opengles2.h>

#include <string>

namespace GL
{
    struct TextureConfig
    {
        std::string path;
        GLint min_filter = GL_NEAREST;
        GLint mag_filter = GL_NEAREST;
        GLint wrap_s = GL_CLAMP_TO_EDGE;
        GLint wrap_t = GL_CLAMP_TO_EDGE;
        GLint gpu_format = GL_RGB;
        GLint format = GL_RGB;
    };

    struct Texture : public Core::Asset
    {
        GLuint id;
        int w, h, ch;
        void* data;
        
        void bind();
        void activate(GLenum);
        Texture(TextureConfig);
        ~Texture();
    };
};