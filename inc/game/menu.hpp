#pragma once

#include "core/state.hpp"
#include "game/menu/background.hpp"

namespace Game::States
{
    struct Menu : public Core::IState
    {
        Objects::Menu::Background bkg;

        virtual void draw() override;
        virtual void update(double dt) override;
    };
};