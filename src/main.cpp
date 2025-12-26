#include "main.hpp"

#include "menu.hpp"

using namespace Game;

States::Main::Main(StateManager &sm) : IState::IState(sm)
{
    // TODO: check later if this is needed elsewhere and cache it in the asset manager if needed.
    this->f_tahoma = std::make_shared<MTSDF::Font>("assets/images/fonts/tahoma.sdf.png", "assets/images/fonts/tahoma.csv");

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

    // TODO: finish the enqueue-ing
    this->loaded_count += AssetManager::queue_from_toml("assets/presets/main.toml");

    this->loaded_count++;
    AssetManager::queue<TextureArray>("t_menu_blip", std::vector{
                                                         TextureConfig{.path = "assets/images/misc/white_bars/1.png"},
                                                         TextureConfig{.path = "assets/images/misc/white_bars/2.png"},
                                                         TextureConfig{.path = "assets/images/misc/white_bars/3.png"},
                                                         TextureConfig{.path = "assets/images/misc/white_bars/4.png"},
                                                         TextureConfig{.path = "assets/images/misc/white_bars/5.png"},
                                                         TextureConfig{.path = "assets/images/misc/white_bars/6.png"},
                                                         TextureConfig{.path = "assets/images/misc/white_bars/7.png"},
                                                     });

    this->loaded_count++;
    AssetManager::queue<TextureArray>("t_menu_background", std::vector{TextureConfig{"assets/images/menu/background/431.png"},
                                                                       TextureConfig{"assets/images/menu/background/440.png"},
                                                                       TextureConfig{"assets/images/menu/background/441.png"},
                                                                       TextureConfig{"assets/images/menu/background/442.png"}});

    this->loaded_count++;
    AssetManager::queue<TextureArray>(
        "t_static", std::vector{TextureConfig{"assets/images/menu/static/12.png"}, TextureConfig{"assets/images/menu/static/13.png"},
                                TextureConfig{"assets/images/menu/static/14.png"}, TextureConfig{"assets/images/menu/static/15.png"},
                                TextureConfig{"assets/images/menu/static/16.png"}, TextureConfig{"assets/images/menu/static/17.png"},
                                TextureConfig{"assets/images/menu/static/18.png"}, TextureConfig{"assets/images/menu/static/20.png"}});

    this->loaded_count++;
    AssetManager::queue<Texture>("t_newspaper", TextureConfig{"assets/images/misc/NEWSPAPER.png"});

    this->loaded_count++;
    AssetManager::queue<TextureArray>("t_blip", std::vector{
                                                    TextureConfig{
                                                        .path = "assets/images/misc/night_bars/4.png",
                                                        .gpu_format = GL_RGBA,
                                                        .format = GL_RGBA,
                                                    },
                                                    TextureConfig{
                                                        .path = "assets/images/misc/night_bars/6.png",
                                                        .gpu_format = GL_RGBA,
                                                        .format = GL_RGBA,
                                                    },
                                                    TextureConfig{
                                                        .path = "assets/images/misc/night_bars/8.png",
                                                        .gpu_format = GL_RGBA,
                                                        .format = GL_RGBA,
                                                    },
                                                    TextureConfig{
                                                        .path = "assets/images/misc/night_bars/9.png",
                                                        .gpu_format = GL_RGBA,
                                                        .format = GL_RGBA,
                                                    },
                                                    TextureConfig{
                                                        .path = "assets/images/misc/night_bars/10.png",
                                                        .gpu_format = GL_RGBA,
                                                        .format = GL_RGBA,
                                                    },
                                                    TextureConfig{
                                                        .path = "assets/images/misc/night_bars/21.png",
                                                        .gpu_format = GL_RGBA,
                                                        .format = GL_RGBA,
                                                    },
                                                    TextureConfig{
                                                        .path = "assets/images/misc/night_bars/22.png",
                                                        .gpu_format = GL_RGBA,
                                                        .format = GL_RGBA,
                                                    },
                                                    TextureConfig{
                                                        .path = "assets/images/misc/night_bars/23.png",
                                                        .gpu_format = GL_RGBA,
                                                        .format = GL_RGBA,
                                                    },
                                                    TextureConfig{
                                                        .path = "assets/images/misc/night_bars/25.png",
                                                        .gpu_format = GL_RGBA,
                                                        .format = GL_RGBA,
                                                    },
                                                });

#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE << "[INFO] Created Main state.\n" << TTY_RESET;
#endif
}

States::Main::~Main()
{
#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE << "[INFO] Destroyed Main state.\n" << TTY_RESET;
#endif
}

void States::Main::draw(int w, int h)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

#ifndef __psp2__
    double scale = std::min(w / 960.0, h / 544.0);
    int s_w = (w - 960 * scale) / 2, s_h = (h - 544 * scale) / 2;
    glViewport(s_w, s_h, w - 2 * s_w, h - 2 * s_h);
#else
    glViewport(0, 0, w, h);
#endif

    for (auto index = 0; index < 3; index++)
    {
        if (AssetManager::enqueued_count() == 0)
            this->t_warning[index]->color.a = (1.0 - this->ti_transition.value / this->ti_transition.rate) * 255;
        else
            this->t_warning[index]->color.a = 255;
        this->t_warning[index]->draw(MTSDF::Font::default_shader);
    }
}

void States::Main::update(double dt)
{
    if (AssetManager::enqueued_count() == 0)
    {
        this->ti_transition.update(dt);
        if (this->ti_transition.has_ticked())
            PUSH_STATE(this->state_manager, Game::States::Menu);
    }
    else
    {
        // TODO: add a loading bar or smth.
        AssetManager::process_enqueued();
    }
}

void States::Main::event(SDL_Event &event)
{
    UNUSED(event);
}
