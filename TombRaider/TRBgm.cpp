#include "TRBgm.h"
#include <iostream>
TRBgm::TRBgm()
{

}

TRBgm::~TRBgm()
{
    Mix_CloseAudio();
    Mix_Quit();
}

void TRBgm::loadMedia(string file)
{

    map<string,Mix_Chunk*>::iterator it = backgroundMusics.find(file);
    if(it!=backgroundMusics.end())
        Mix_PlayChannel(-1,it->second,0);
    Mix_Chunk * mMusic = Mix_LoadWAV(file.c_str());
    if(mMusic == NULL)
    {
        cerr << "failed to loaded wav " <<file << " " << Mix_GetError()<<endl;
    }
    backgroundMusics[file] = mMusic;
    Mix_PlayChannel(-1,mMusic,0);
}

void TRBgm::playMusic(string file,bool loop)
{
    /*pauseMusic();
    Mix_FreeMusic(gMusic);
    gMusic = Mix_LoadMUS(file.c_str());
    if(gMusic == NULL)
    {
        cerr << "Failed to load music " << file << " " << Mix_GetError()<<endl;
    }
    if(loop)
        Mix_PlayMusic(gMusic,-1);
    else
        Mix_PlayMusic(gMusic,1);*/
    cerr << "will load music : " << file << endl;
    Mix_Chunk * gChunk = Mix_LoadWAV(file.c_str());
    cerr << SDL_GetError() << endl;
	if(loop)
	Mix_PlayChannel(-1,gChunk,0);
}

void TRBgm::pauseMusic()
{
    Mix_PauseMusic();
}

bool TRBgm::isMusicPause()
{
    bool isPause = Mix_PausedMusic() || !Mix_PlayingMusic();
    return isPause;
}
