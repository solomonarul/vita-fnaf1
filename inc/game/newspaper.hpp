#pragma once

#include <nex.hpp>

using namespace NEX::Core;
using namespace NEX::GL;

namespace Game::States
{
    struct Newspaper : public IState
    {
        Newspaper(StateManager &);
        ~Newspaper();

        std::shared_ptr<Shader> s_texture_default;
        std::shared_ptr<Texture> t_newspaper;

        enum
        {
            NEWSPAPER_STATE_FADING_IN = 0,
            NEWSPAPER_STATE_HOLD,
            NEWSPAPER_STATE_FADING_OUT
        } state = NEWSPAPER_STATE_FADING_IN;

        GLuint vbo = 0;
        double alpha = 0;
        double hold_timer = 0;

        static constexpr double timer_duration = 2;
        static constexpr double inverse_timer_duration = 1.0 / timer_duration;

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event &) override;
    };
}; // namespace Game::States
