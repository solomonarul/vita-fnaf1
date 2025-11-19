#pragma once

#include "core/asset.hpp"

#include <SDL3/SDL_opengles2.h>

#include <fstream>

namespace GL
{
    struct VertexShader
    {
        GLuint id = 0;

        VertexShader(std::ifstream);
        VertexShader(std::string);
        ~VertexShader();
    };

    struct FragmentShader
    {
        GLuint id = 0;

        FragmentShader(std::ifstream);
        FragmentShader(std::string);
        ~FragmentShader();
    };

    struct Shader : public Core::Asset
    {
        GLuint id = 0;
        
        void use();
        Shader(const VertexShader&, const FragmentShader&);
        Shader(std::string, std::string);
        ~Shader();
    };
};