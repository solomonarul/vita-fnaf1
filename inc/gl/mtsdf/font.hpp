#pragma once

#include "core/asset.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"

#include <SDL3/SDL.h>

#include <memory>
#include <string>
#include <map>

namespace GL::MTSDF
{
    struct Font : public Core::Asset
    {
        std::unique_ptr<Texture> texture;
        size_t count_x, count_y;
        std::map<char, SDL_FRect> rects;
        std::string path;

        static std::unique_ptr<GL::Shader> default_shader;

        Font(const std::string&, size_t = 10, size_t = 10, std::string = "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~      ");
        ~Font();
    };
}