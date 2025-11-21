#pragma once

#include <cstdint>

namespace Core
{
    class Delta
    {
    public:
        Delta();
        double tick();

    private:
        uint64_t last;
    };
};

