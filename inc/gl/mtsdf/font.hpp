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
    struct GlyphData
    {
        float advance;
        SDL_FRect quad;
        SDL_FRect atlas;
    };

    struct Font : public Core::Asset
    {
        std::unique_ptr<Texture> texture;
        std::map<char, GlyphData> glyphs;
        std::string path;

        static std::unique_ptr<GL::Shader> default_shader;

        Font(const std::string&, const std::string&);
        ~Font();
    };
}