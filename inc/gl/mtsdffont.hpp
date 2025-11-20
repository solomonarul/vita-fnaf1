#pragma once

#include "core/asset.hpp"
#include "gl/texture.hpp"

#include <SDL3/SDL.h>

#include <memory>
#include <string>
#include <map>

namespace GL
{
    struct MTSDFFont : public Core::Asset
    {
        std::unique_ptr<Texture> texture;
        size_t count_x, count_y;
        std::map<char, SDL_FRect> rects;
        std::string path;

        MTSDFFont(const std::string&, size_t = 10, size_t = 10, std::string = "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~      ");
        ~MTSDFFont();
    };
}