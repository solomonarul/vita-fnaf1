#include "gl/shader.hpp"

#include "core/defines.hpp"
#include "core/file.hpp"

#include <iostream>

using namespace GL;

static GLchar log[512];

VertexShader::VertexShader(std::ifstream& file) : VertexShader(Core::read_file_contents(file)) {}

VertexShader::VertexShader(std::string code)
{
    this->id = glCreateShader(GL_VERTEX_SHADER);
    const char* code_str = code.c_str();
    glShaderSource(this->id, 1, &code_str, NULL);
    glCompileShader(this->id);

    static GLint success;
    glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(this->id, sizeof(log), NULL, log);
        std::cerr << TTY_RED << "[EROR]: Vertex shader compilation error:\n" << TTY_YELLOW << log << "\n" << TTY_RESET;
        this->id = 0;
        return;
    }

    std::cout << TTY_BLUE << "[INFO]: Loaded vertex shader (id: " << this->id << ")\n" << TTY_RESET;
}

VertexShader::~VertexShader()
{
    if(this->id != 0)
        glDeleteShader(this->id), std::cout << TTY_BLUE << "[INFO]: Destroyed vertex shader (id: " << this->id << ")\n" << TTY_RESET;
}

FragmentShader::FragmentShader(std::ifstream& file) : FragmentShader(Core::read_file_contents(file)) {}

FragmentShader::FragmentShader(std::string code)
{
    this->id = glCreateShader(GL_FRAGMENT_SHADER);
    const char* code_str = code.c_str();
    glShaderSource(this->id, 1, &code_str, NULL);
    glCompileShader(this->id);

    static GLint success;
    glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(this->id, sizeof(log), NULL, log);
        std::cerr << TTY_RED << "[EROR]: Fragment shader compilation error:\n" << TTY_YELLOW << log << "\n" << TTY_RESET;
        this->id = 0;
        return;
    }

    std::cout << TTY_BLUE << "[INFO]: Loaded fragment shader (id: " << this->id << ")\n" << TTY_RESET;
}

FragmentShader::~FragmentShader()
{
    if(this->id != 0)
        glDeleteShader(this->id), std::cout << TTY_BLUE << "[INFO]: Destroyed fragment shader (id: " << this->id << ")\n" << TTY_RESET;
}

Shader::Shader(const VertexShader& vert, const FragmentShader& frag)
{
    this->id = glCreateProgram();
    if(vert.id != 0)
        glAttachShader(this->id, vert.id);

    if(frag.id != 0)
        glAttachShader(this->id, frag.id);

    glLinkProgram(id);

    static GLint linkStatus = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);

    if(!linkStatus)
    {
        glGetProgramInfoLog(this->id, sizeof(log), NULL, log);
        std::cerr << TTY_RED << "[EROR]: General shader linking error:\n" << TTY_YELLOW << log << "\n" << TTY_RESET;
        this->id = 0;
        return;
    }

    std::cout << TTY_BLUE << "[INFO]: Loaded full shader (id: " << this->id << ") made out of vertex (id: " << vert.id << ") and fragment (id: " << frag.id << ") shaders.\n" << TTY_RESET;
}

void Shader::use()
{
    glUseProgram(this->id);
}

Shader::~Shader()
{
    if(this->id != 0)
        glDeleteProgram(id), std::cout << TTY_BLUE << "[INFO]: Destroyed full shader (id: " << this->id << ")\n" << TTY_RESET;
}
