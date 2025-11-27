#pragma once

namespace Core
{
    struct Timer
    {
        bool ok = false;
        double value = 0, rate;
        Timer(double);
        void update(double);
        bool has_ticked(void);
    };
};