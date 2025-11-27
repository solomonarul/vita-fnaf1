#pragma once

#include "core/state.hpp"
#include "gl/mtsdf/text.hpp"
#include "gl/mtsdf/font.hpp"

namespace Game::States
{
    struct NightLoader : public Core::IState
    {
        NightLoader(Core::StateManager&, int);
        ~NightLoader();

        std::shared_ptr<GL::MTSDF::Font> f_lcdsolid;
        std::unique_ptr<GL::MTSDF::Text> t_night[2];

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event&) override;
    };
};