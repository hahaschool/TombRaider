//
//  TRAnimator.cpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRAnimator.hpp"
//class TRAnimator{
//public:
//    TRAnimator();
//    ~TRAnimator();
//    void free();
//    void clearSequence();
//    void appendClipRect(SDL_Rect rect);
//    int getAnimationPeriod();
//    void setRateByPeriod(int nap);
//    void setRateByFramePerClip();
//    bool isLoop();
//    void setLoop(bool flg);
//    void animate();//Progress one frame
//    SDL_Rect getCurrentClipRect();
//private:
//    int frameCnt;
//    bool flgLoop;
//    int animationPeriod;//Calculated by frame
//    std::vector<SDL_Rect> seq;
//};
//

TRAnimator::TRAnimator(){
    frameCnt = 0;
    seq.clear();
    animationPeriod = 0;
    curidx = 0;
    totalCnt = 0;
}

TRAnimator::~TRAnimator(){
    free();
}

void TRAnimator::free(){
    frameCnt = 0;
    curidx = 0;
    totalCnt = 0;
    seq.clear();
    animationPeriod = 0;
}

void TRAnimator::clearSequence(){
    seq.clear();
}

void TRAnimator::appendClipRect(SDL_Rect rect){
    seq.emplace_back(rect);
}

int TRAnimator::getAnimationPeriod(){
    return animationPeriod;
}

int TRAnimator::getFramePerClip(){
    return framePerClip;
}

void TRAnimator::setRateByFramePerClip(int fpc){
    framePerClip = fpc;
    animationPeriod = fpc * (int)seq.size();
}

void TRAnimator::setRateByPeriod(int nap){
    animationPeriod = nap;
    framePerClip = nap / (int)seq.size();
}

void TRAnimator::reset(){
    curidx = 0;
    frameCnt = 0;
}

void TRAnimator::animate(){
    if (flgEnd) {
        return;
    }
    totalCnt++;
    if(!flgLoop && totalCnt > animationPeriod){
        flgEnd = true;
        return;
    }
    frameCnt++;
    if(frameCnt > framePerClip){
        frameCnt = 0;
        curidx++;
    }
    if(curidx >= seq.size()){
        curidx = 0;
    }
}

SDL_Rect TRAnimator::getCurrentClipRect(){
    return seq[curidx];
}

bool TRAnimator::isLoop(){
    return flgLoop;
}

void TRAnimator::setLoop(bool flg){
    flgLoop = flg;
}

bool TRAnimator::isEnd(){
    return flgEnd;
}

