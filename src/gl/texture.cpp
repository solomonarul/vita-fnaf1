#include "gl/texture.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "gl/stb_image.h"

#include "core/defines.hpp"

using namespace GL;

Texture::Texture(TextureConfig cfg)
{
    glGenTextures(1, &this->id);
    this->bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, cfg.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, cfg.mag_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, cfg.wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, cfg.wrap_t);

    this->data = stbi_load(cfg.path.c_str(), &this->w, &this->h, &this->ch, 0);
    if(!this->data)
    {
        std::cerr << TTY_RED << "[EROR]: Could not load texture (path: " << cfg.path << "): " << stbi_failure_reason() << "\n" << TTY_RESET;
        return;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, cfg.gpu_format, this->w, this->h, 0, cfg.format, GL_UNSIGNED_BYTE, this->data);
    std::cout << TTY_BLUE << "[INFO]: Loaded texture (id: " << this->id << ") (path: " << cfg.path << ") (w: " << this->w << ") (h: " << this->h << ") (ch: " << this->ch << ")\n" << TTY_RESET;

    stbi_image_free(this->data);
    this->data = nullptr;
}

void Texture::activate(GLenum slot)
{
    glActiveTexture(slot);
    this->bind();
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

Texture::~Texture()
{
    if(this->id)
    {
        if(this->data)
            stbi_image_free(this->data);
        
        glDeleteTextures(1, &this->id);
        std::cout << TTY_BLUE << "[INFO]: Destroyed texture (id: " << this->id << ")\n" << TTY_RESET;
    }
}