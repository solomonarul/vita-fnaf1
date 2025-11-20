#pragma once

#include "core/state.hpp"
#include "gl/mtsdffont.hpp"

namespace Game::States
{
    struct MainLoading : public Core::IState
    {
        MainLoading();
        ~MainLoading();

        std::shared_ptr<GL::MTSDFFont> f_consolas;

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
    };
};