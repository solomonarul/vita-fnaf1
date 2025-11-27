#pragma once

#include "core/asset.hpp"
#include "gl/defines.hpp"

#include <fstream>

namespace GL
{
    struct VertexShader
    {
        GLuint id = 0;

        VertexShader(std::ifstream&);
        VertexShader(std::string);
        ~VertexShader();
    };

    struct FragmentShader
    {
        GLuint id = 0;

        FragmentShader(std::ifstream&);
        FragmentShader(std::string);
        ~FragmentShader();
    };

    struct Shader : public Core::IAsset
    {
        GLuint id = 0;
        
        void use();
        Shader(std::string, std::string);
        Shader(const VertexShader&, const FragmentShader&);
        ~Shader();
    };
};