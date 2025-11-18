#include "core/file.hpp"
#include <iostream>

using namespace Core;

std::string Core::read_file_contents(std::ifstream& file)
{
    if(!file.good() || file.eof())
        return "";

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    std::string buffer(size, '\0');
    file.seekg(0);

    file.read(buffer.data(), size);
    return buffer;
}