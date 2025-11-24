#include "gl/assets/textureatlas.hpp"

using namespace GL;

TextureAtlas::TextureAtlas(std::vector<TextureConfig> cfgs)
{
    for(auto cfg : cfgs)
        this->textures.push_back(std::make_shared<Texture>(cfg));
}