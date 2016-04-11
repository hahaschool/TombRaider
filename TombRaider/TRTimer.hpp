//
//  TRTimer.hpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRTimer_hpp
#define TRTimer_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

//Returns ms
class TRTimer{
public:
    //Constructor
    TRTimer();
    
    //Clocking Actions
    void start();
    void stop();
    void pause();
    void resume();
    
    //Gets the timer's time
    Uint32 getTicks();
    
    //Checking status
    bool isStarted();
    bool isPaused();
    
protected:
    
private:
    //The clock time when timer is started
    Uint32 mStartTicks;
    
    //The ticks stored when timer is paused;
    Uint32 mPausedTicks;
    
    //Status flags
    bool flgPaused;
    bool flgStarted;
    
};

#endif /* TRTimer_hpp */
