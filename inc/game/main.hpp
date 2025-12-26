#pragma once

#include <nex.hpp>

using namespace NEX::Core;
using namespace NEX::GL;

namespace Game::States
{
    struct Main : public IState
    {
        Main(StateManager &);
        ~Main();

        size_t loaded_count = 0;
        std::unique_ptr<MTSDF::Text> t_warning[3];
        std::shared_ptr<MTSDF::Font> f_tahoma;

        Timer ti_transition = Timer(3.0);

        virtual void draw(int w, int h) override;
        virtual void update(double dt) override;
        virtual void event(SDL_Event &) override;
    };
}; // namespace Game::States
