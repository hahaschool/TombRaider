//
//  TRTimer.cpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRTimer.hpp"

TRTimer::TRTimer(){
    //Initializing Variables
    mStartTicks = 0;
    mPausedTicks = 0;
    flgPaused = false;
    flgStarted = false;
}

void TRTimer::start(){
    //Start the timer
    flgStarted = true;
    //Unpause the timer
    flgPaused = false;
    //Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void TRTimer::stop(){
    //Stop the timer
    flgStarted = false;
    //Unpause the timer
    flgPaused = false;
    //Clear Tick Variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void TRTimer::pause(){
    //If the timer is running and isn't already running
    if (flgStarted && !flgPaused) {
        //Pause the timer
        flgPaused = true;
        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void TRTimer::resume(){
    //If the timer is running and paused
    if(flgStarted && flgPaused){
        flgPaused = false;
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        mPausedTicks = 0;
    }
}

Uint32 TRTimer::getTicks(){
    Uint32 time = 0;
    if(flgStarted){
        if(flgPaused){
            time = mPausedTicks;
        }else{
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}

bool TRTimer::isStarted(){
    return flgStarted;
}

bool TRTimer::isPaused(){
    return flgPaused;
}

