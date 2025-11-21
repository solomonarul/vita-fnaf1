#include "gl/mtsdf/font.hpp"

using namespace GL;

#include "core/defines.hpp"
#include "gl/shader.hpp"

#include <iostream>

std::unique_ptr<GL::Shader> MTSDF::Font::default_shader;

MTSDF::Font::Font(const std::string& path, size_t count_x, size_t count_y, std::string charset)
{
    if(!default_shader)
        default_shader = std::make_unique<GL::Shader>("assets/shaders/mtsdf_default.vert", "assets/shaders/mtsdf_default.frag");
    
    this->texture = std::make_unique<Texture>(GL::TextureConfig{
        .path = path,
        .min_filter = GL_LINEAR,
        .mag_filter = GL_LINEAR,
        .gpu_format = GL_RGBA,
        .format = GL_RGBA,
    });
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

    std::cout << TTY_BLUE << "[INFO]: Loaded MTSDF font (path: " << this->path << ") (count_x: " << count_x << ") (count_y: " << count_y << ")\n" << TTY_RESET;
}

MTSDF::Font::~Font()
{
    std::cout << TTY_BLUE << "[INFO]: Destroyed MTSDF font (path: " << this->path << ")\n" << TTY_RESET;
}