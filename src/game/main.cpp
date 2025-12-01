#include "game/main.hpp"

#include "core/defines.hpp"
#include "core/assetmanager.hpp"
#include "game/menu.hpp"

using namespace Game;

States::Main::Main(Core::StateManager& sm) : IState::IState(sm)
{
    this->f_tahoma = std::make_shared<GL::MTSDF::Font>("assets/images/fonts/tahoma.sdf.png", "assets/images/fonts/tahoma.csv");

    this->t_warning[0] = std::make_unique<GL::MTSDF::Text>(f_tahoma, "WARNING!");
    this->t_warning[0]->y = 90 / 544.0;
    
    this->t_warning[1] = std::make_unique<GL::MTSDF::Text>(f_tahoma, "This game contains flashing lights, loud");
    this->t_warning[1]->y = 0 / 544.0;

    this->t_warning[2] = std::make_unique<GL::MTSDF::Text>(f_tahoma, "noises, and lots of jumpscares!");
    this->t_warning[2]->y = -45 / 544.0;

    for(auto index = 0; index < 3; index++)
    {
        this->t_warning[index]->x = 0;
        this->t_warning[index]->o_x = -0.5;
        this->t_warning[index]->s = 45 / 544.0;
        this->t_warning[index]->s_x = 0.6;
    }

    // Preload a shitton of stuff.
    // TODO: move to a better system or smth. Just inlining everything here feels bad. ALso I will probably have 2 loading screens.

    this->loaded_count++;
    Core::AssetManager::queue<GL::Shader>("s_menu_background",
        "assets/shaders/menu/background.vert",
        "assets/shaders/menu/background.frag"
    );

    this->loaded_count++;
    Core::AssetManager::queue<GL::TextureAtlas>("t_menu_blip", std::vector{
        GL::TextureConfig{.path = "assets/images/misc/white_bars/1.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/2.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/3.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/4.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/5.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/6.png"},
        GL::TextureConfig{.path = "assets/images/misc/white_bars/7.png"},
    });

    this->loaded_count++;
    Core::AssetManager::queue<GL::TextureAtlas>("t_menu_background", std::vector{
        GL::TextureConfig{"assets/images/menu/background/431.png"},
        GL::TextureConfig{"assets/images/menu/background/440.png"},
        GL::TextureConfig{"assets/images/menu/background/441.png"},
        GL::TextureConfig{"assets/images/menu/background/442.png"}
    });

    this->loaded_count++;
    Core::AssetManager::queue<GL::TextureAtlas>("t_static", std::vector{
        GL::TextureConfig{"assets/images/menu/static/12.png"},
        GL::TextureConfig{"assets/images/menu/static/13.png"},
        GL::TextureConfig{"assets/images/menu/static/14.png"},
        GL::TextureConfig{"assets/images/menu/static/15.png"},
        GL::TextureConfig{"assets/images/menu/static/16.png"},
        GL::TextureConfig{"assets/images/menu/static/17.png"},
        GL::TextureConfig{"assets/images/menu/static/18.png"},
        GL::TextureConfig{"assets/images/menu/static/20.png"}
    });

    this->loaded_count++;
    Core::AssetManager::queue<GL::MTSDF::Font>(
        "f_consolas",
        "assets/images/fonts/consolas.sdf.png", "assets/images/fonts/consolas.csv"
    );

    this->loaded_count++;
    Core::AssetManager::queue<Core::Audio>("a_static2", "assets/audio/menu/static2.mp3", true);

    this->loaded_count++;
    Core::AssetManager::queue<Core::Audio>("a_darkness_music", "assets/audio/menu/darkness music.mp3", true);

    this->loaded_count++;
    Core::AssetManager::queue<Core::Audio>("a_blip3", "assets/audio/blip3.mp3", true);

    this->loaded_count++;
    Core::AssetManager::queue<GL::Texture>("t_newspaper", GL::TextureConfig{"assets/images/misc/NEWSPAPER.png"});

    this->loaded_count++;
    Core::AssetManager::queue<GL::MTSDF::Font>(
        "f_consolas_bold",
        "assets/images/fonts/consolas_bold.sdf.png", "assets/images/fonts/consolas_bold.csv"
    );

    this->loaded_count++;
    Core::AssetManager::queue<GL::MTSDF::Font>(
        "f_lcdsolid",
        "assets/images/fonts/lcdsolid.sdf.png", "assets/images/fonts/lcdsolid.csv"
    );

    this->loaded_count++;
    Core::AssetManager::queue<GL::TextureAtlas>("t_blip", std::vector{
        GL::TextureConfig{.path = "assets/images/misc/night_bars/4.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_bars/6.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_bars/8.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_bars/9.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_bars/10.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_bars/21.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_bars/22.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_bars/23.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
        GL::TextureConfig{.path = "assets/images/misc/night_bars/25.png", .gpu_format = GL_RGBA, .format = GL_RGBA, },
    });

#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE <<  "[INFO]: Created Main state.\n" << TTY_RESET;
#endif
}

States::Main::~Main()
{
#ifdef SCENE_LOAD_LOG
    std::cout << TTY_BLUE <<  "[INFO]: Destroyed Main state.\n" << TTY_RESET;
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

    for(auto index = 0; index < 3; index++)
    {
        if(Core::AssetManager::enqueued_count() == 0)
            this->t_warning[index]->color.a = (1.0 - this->ti_transition.value / this->ti_transition.rate) * 255;
        else
            this->t_warning[index]->color.a = 255;
        this->t_warning[index]->draw(GL::MTSDF::Font::default_shader);
    }
}

void States::Main::update(double dt)
{
    if(Core::AssetManager::enqueued_count() == 0)
    {
        this->ti_transition.update(dt);
        if(this->ti_transition.has_ticked())
            this->state_manager.states.push_back(std::make_shared<Game::States::Menu>(this->state_manager));
    }
    else
    {
        // TODO: add a loading bar or smth.
        Core::AssetManager::process_enqueued();
    }
}

void States::Main::event(SDL_Event& event)
{
    UNUSED(event);
}