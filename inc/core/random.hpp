#pragma once
#include <random>
#include <concepts>
#include <algorithm>

namespace Core
{
    // I stole this, don't cite me.
    // TODO: review this.
    struct Random {
    public:
        // ------------------------
        //  Integer range [min, max]
        // ------------------------
        template<std::integral Int>
        static Int range(Int min, Int max) {
            thread_local std::mt19937_64 rng{ std::random_device{}() };
            std::uniform_int_distribution<Int> dist(min, max);
            return dist(rng);
        }

        // ------------------------
        //  Float range [min, max)
        // ------------------------
        template<std::floating_point FP>
        static FP range(FP min, FP max) {
            thread_local std::mt19937_64 rng{ std::random_device{}() };
            std::uniform_real_distribution<FP> dist(min, max);
            return dist(rng);
        }

        // ------------------------
        //  [0,1)
        // ------------------------
        static double unit() {
            return range(0.0, 1.0);
        }

        // ------------------------
        //  True/false (50/50)
        // ------------------------
        static bool boolean() {
            return range(0, 1) == 1;
        }

        // ------------------------
        //  Pick a random element
        // ------------------------
        template<class Container>
        static const auto& choice(const Container& c) {
            return c[range<std::size_t>(0, c.size() - 1)];
        }

        // ------------------------
        //  Shuffle container
        // ------------------------
        template<class Container>
        static void shuffle(Container& c) {
            thread_local std::mt19937_64 rng{ std::random_device{}() };
            std::shuffle(c.begin(), c.end(), rng);
        }
    };
}
