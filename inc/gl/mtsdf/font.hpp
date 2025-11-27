#pragma once

#include "core/asset.hpp"
#include "gl/defines.hpp"
#include "gl/assets/shader.hpp"
#include "gl/assets/texture.hpp"

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

    struct Font : public Core::IAsset
    {
        std::unique_ptr<Texture> texture;
        std::map<char, GlyphData> glyphs;
        std::string path;

        static std::unique_ptr<GL::Shader> default_shader;

        Font(const std::string&, const std::string&);
        ~Font();
    };
}