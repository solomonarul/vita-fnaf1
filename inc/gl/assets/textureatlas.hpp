#pragma once

#include "texture.hpp"

#include <memory>
#include <vector>

namespace GL
{
    struct TextureAtlas : public Core::IAsset
    {
        std::vector<std::shared_ptr<Texture>> textures;
        TextureAtlas(std::vector<TextureConfig>);
    };
};