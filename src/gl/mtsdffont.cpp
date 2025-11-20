#include "gl/mtsdffont.hpp"

using namespace GL;

#include "core/defines.hpp"

#include <iostream>

MTSDFFont::MTSDFFont(const std::string& path, size_t count_x, size_t count_y, std::string charset)
{
    this->texture = std::make_unique<Texture>(path);
    this->count_x = count_x, this->count_y = count_y;

    size_t index = 0;
    double char_w = 1.0 / this->count_x, char_h = 1.0 / this->count_y;
    for(auto& character : charset)
    {
        SDL_FRect& current = rects[character];
        int x = index % count_x, y = index / count_y;
        current.x = x * char_w;
        current.y = y * char_h;
        current.w = char_w;
        current.h = char_h;
        index++;
    }
    this->path = path;

    std::cout << TTY_BLUE << "[INFO]: Loaded MTSDF Font (path: " << this->path << ") (count_x: " << count_x << ") (count_y: " << count_y << ")\n" << TTY_RESET;
}

MTSDFFont::~MTSDFFont()
{
    std::cout << TTY_BLUE << "[INFO]: Destroyed MTSDF Font (path: " << this->path << ")\n" << TTY_RESET;
}