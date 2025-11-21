#pragma once

#include "gl/mtsdf/font.hpp"
#include "gl/shader.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengles2.h>
#include <string>
#include <memory>
#include <vector>

namespace GL::MTSDF
{
    struct Text
    {
        std::shared_ptr<Font> font;
        std::string text;
        float x = 0.0f, y = 0.0f, w = 1.0f, h = 1.0f;
        float s = 1.0f;
        SDL_Color color = {255, 255, 255, 255};

        // GLES2 VBO
        GLuint vbo = 0;
        std::vector<float> vertexData; // x, y, u, v per vertex

        Text(std::shared_ptr<Font>, const std::string&);
        ~Text();

        void draw(std::unique_ptr<GL::Shader>&);
    };
}
