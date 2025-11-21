#pragma once

#include "core/state.hpp"
#include "gl/mtsdf/text.hpp"
#include "gl/mtsdf/font.hpp"

namespace Game::States
{
    struct MainLoading : public Core::IState
    {
        MainLoading();
        ~MainLoading();

        std::unique_ptr<GL::MTSDF::Text> t_warning;
        std::shared_ptr<GL::MTSDF::Font> f_consolas;

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
    };
};