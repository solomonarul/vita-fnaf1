#include "game/menu.hpp"

using namespace Game;

States::Menu::Menu()
{
    SDL_AudioSpec spec{.format = SDL_AUDIO_S16, .channels = 2, .freq = 44100};

    this->a_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
    this->a_static2 = MIX_LoadAudio(this->a_mixer, "assets/audio/static2.mp3", true);
    this->a_darkness_music = MIX_LoadAudio(this->a_mixer, "assets/audio/darkness music.mp3", true);
    this->a_blip3 = MIX_LoadAudio(this->a_mixer, "assets/audio/blip3.mp3", true);

    MIX_PlayAudio(this->a_mixer, this->a_static2);

    this->a_darkness_music_track = MIX_CreateTrack(this->a_mixer);
    MIX_SetTrackAudio(this->a_darkness_music_track, this->a_darkness_music);
    MIX_PlayTrack(this->a_darkness_music_track, 0);
    MIX_PlayAudio(this->a_mixer, this->a_blip3);
}

States::Menu::~Menu()
{
    MIX_StopTrack(this->a_darkness_music_track, 0);
    MIX_DestroyTrack(this->a_darkness_music_track);
    MIX_DestroyAudio(this->a_static2);
    MIX_DestroyAudio(this->a_darkness_music);
    MIX_DestroyAudio(this->a_blip3);
}

void States::Menu::draw(int w, int h)
{
#ifndef __psp2__
    double scale = std::min(w / 960.0, h / 544.0);
    int s_w = (w - 960 * scale) / 2, s_h = (h - 544 * scale) / 2;
    glViewport(s_w, s_h, w - 2 * s_w, h - 2 * s_h);
#else
    glViewport(0, 0, w, h);
#endif
    this->bkg.draw();
}

void States::Menu::update(double dt)
{
    if(!MIX_TrackPlaying(this->a_darkness_music_track))
        MIX_PlayTrack(this->a_darkness_music_track, 0);

    this->bkg.update(dt);
}