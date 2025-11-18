#include "gl/texture.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "gl/stb_image.h"

#include "core/defines.hpp"

using namespace GL;

Texture::Texture(std::string path)
{
    glGenTextures(1, &this->id);
    this->bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    this->data = stbi_load(path.c_str(), &this->w, &this->h, &this->ch, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->w, this->h, 0, GL_RGB, GL_UNSIGNED_BYTE, this->data);
    std::cout << TTY_BLUE << "[INFO]: Loaded texture (id: " << this->id << ") (path: " << path << ") (w: " << this->w << ") (h: " << this->h << ") (ch: " << this->ch << ")\n" << TTY_RESET;
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
        glDeleteTextures(1, &this->id);
        std::cout << TTY_BLUE << "[INFO]: Destroyed texture (id: " << this->id << ")\n" << TTY_RESET;
    }
}