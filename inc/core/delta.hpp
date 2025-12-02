#pragma once

#include <cstdint>

namespace Core
{
    class DeltaTimer
    {
    public:
        DeltaTimer();
        double tick();

    private:
        uint64_t last;
    };
};

