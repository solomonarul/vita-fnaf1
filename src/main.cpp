#include "main.hpp"

#include "assets/main.hpp"
#include "menu.hpp"

using namespace Game;

States::Main::Main(StateManager& sm) : IState::IState(sm)
{
    this->f_tahoma = AssetManager::ensure_loaded<MTSDF::Font>("f_tahoma", "assets/images/fonts/tahoma.sdf.png", "assets/images/fonts/tahoma.csv");

    this->t_warning[0] = std::make_unique<MTSDF::Text>(f_tahoma, "WARNING!");
    this->t_warning[0]->y = 90 / 544.0;

    this->t_warning[1] = std::make_unique<MTSDF::Text>(f_tahoma, "This game contains flashing lights, loud");
    this->t_warning[1]->y = 0 / 544.0;

    this->t_warning[2] = std::make_unique<MTSDF::Text>(f_tahoma, "noises, and lots of jumpscares!");
    this->t_warning[2]->y = -45 / 544.0;

    for (auto index = 0; index < 3; index++)
    {
        this->t_warning[index]->x = 0;
        this->t_warning[index]->o_x = -0.5;
        this->t_warning[index]->s = 45 / 544.0;
        this->t_warning[index]->s_x = 0.6;
    }

    // clang-format off
    this->t_loader = AssetManager::ensure_loaded<Texture>("t_loader", TextureConfig{
        .path = "assets/images/misc/LITTLE_CLOCK.png",
        .min_filter = GL_LINEAR,
        .mag_filter = GL_LINEAR,
    });
    this->o_cursor = std::make_shared<Objects::Cursor>(std::make_shared<Texture>(TextureConfig{
        .path = "assets/images/cursor.png",
    }), 8, 3);
    // clang-format on

    this->spr_loader.refresh_from_rect(SDL_FRect{.x = 856.0 / 960, .y = -500.0 / 544, .w = 64.0 / 960, .h = 64.0 / 544});

    queue_assets(&this->loaded_count);
}

void States::Main::draw(int w, int h)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    NEX::GL::set_view_letterbox({w, h}, {960, 544});

    for (auto index = 0; index < 3; index++)
    {
        if (AssetManager::enqueued_count() == 0)
            this->t_warning[index]->color.a = (1.0 - this->ti_transition.progress()) * 255;
        else
            this->t_warning[index]->color.a = 255;
        this->t_warning[index]->draw(MTSDF::Font::default_shader);
    }

    if (AssetManager::enqueued_count() != 0)
    {
        Texture::default_shader->use();
        Texture::default_shader->setUniform("u_texture", 0);
        this->t_loader->activate(GL_TEXTURE0);
        this->spr_loader.draw(*Texture::default_shader);
    }

    Texture::default_shader->use();
    this->o_cursor->draw(*Texture::default_shader);
}

void States::Main::update(double dt)
{
    this->o_cursor->update();

    if (AssetManager::enqueued_count() == 0)
    {
        this->ti_transition.update(dt);
        if (this->ti_transition.has_ticked())
            PUSH_STATE(this->state_manager, Game::States::Menu, this->o_cursor);
    }
    else
        AssetManager::process_enqueued();
}

void States::Main::event(SDL_Event& event)
{
    switch (event.type)
    {
#if !defined(__psp2__)
        case SDL_EVENT_KEY_DOWN:
#endif
        case SDL_EVENT_MOUSE_BUTTON_UP:
            this->ti_transition.update(this->ti_transition.rate);
            break;
    }

    this->o_cursor->event(event);
}
