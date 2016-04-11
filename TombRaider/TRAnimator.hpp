//
//  TRAnimator.hpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRAnimator_hpp
#define TRAnimator_hpp

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

class TRAnimator{
public:
    TRAnimator();
    ~TRAnimator();
    void free();
    void clearSequence();
    void appendClipRect(SDL_Rect rect);
    int getAnimationPeriod();
    void setRateByPeriod(int nap);
    void setRateByFramePerClip(int fpc);
    void animate();//Progress one frame
    void reset();
    SDL_Rect getCurrentClipRect();
    int getFramePerClip();
    bool isLoop();
    void setLoop(bool flg);
    bool isEnd();
private:
    bool flgLoop;
    bool flgEnd;
    int frameCnt;
    int totalCnt;
    int curidx;
    int animationPeriod;//Calculated by frame
    int framePerClip;
    std::vector<SDL_Rect> seq;
};

#endif /* TRAnimator_hpp */
