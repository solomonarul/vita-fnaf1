#pragma once

#include "core/state.hpp"
#include "gl/mtsdf/text.hpp"
#include "gl/mtsdf/font.hpp"

namespace Game::States
{
    struct Main : public Core::IState
    {
        Main(Core::StateManager&);
        ~Main();

        std::unique_ptr<GL::MTSDF::Text> t_warning[3];
        std::shared_ptr<GL::MTSDF::Font> f_tahoma;

        double timer = 0;

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event&) override;
    };
};