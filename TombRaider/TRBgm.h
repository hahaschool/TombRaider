#ifndef TRBGM_H_INCLUDED
#define TRBGM_H_INCLUDED

#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <map>

using namespace std;

class TRBgm{
public:
    TRBgm();
    ~TRBgm();
    void loadMedia(string file);
    void playMusic(string file,bool loop);
    void pauseMusic();
    bool isMusicPause();

private:
    Mix_Music *gMusic;
    map<string, Mix_Chunk*>backgroundMusics;

};

#endif // TRBGM_H_INCLUDED
