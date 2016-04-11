//
//  TRSprite.cpp
//  TombRaider
//
//  Created by 張正昊 on 13/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRSprite.hpp"
TRSprite::TRSprite(){
    mVelX = mVelY = 0;
    flgMovingAnimated = false;
    flgStaticAnimated = false;
    flgFreeze = false;
    flgMoving = false;
    mDirection = TRDirectionUp;
}

void TRSprite::setVelX(int velX){
    mVelX = velX;
}

void TRSprite::setVelY(int velY){
    mVelY = velY;
}

void TRSprite::setVelXY(int velXY){
    mVelX = mVelY = velXY;
}

int TRSprite::getVelX(){
    return mVelX;
}

int TRSprite::getVelY(){
    return mVelY;
}

void TRSprite::setDirection(int dir){
    mDirection = dir;
}

int TRSprite::getDirection(){
    return mDirection;
}

bool TRSprite::isMovingAnimated(){
    return flgMovingAnimated;
}

bool TRSprite::isStaticAnimated(){
    return flgStaticAnimated;
}

void TRSprite::setMovingAnimated(bool flg){
    flgMovingAnimated = flg;
}

void TRSprite::setStaticAnimated(bool flg){
    flgStaticAnimated = flg;
}

void TRSprite::linkMovingAnimator(TRAnimator *animator, TRDirection dir){
    mMovingAnimator[dir] = animator;
}

void TRSprite::linkStaticAnimator(TRAnimator *animator, TRDirection dir){
    mStaticAnimator[dir] = animator;
}

void TRSprite::freeze(){
    flgFreeze = true;
    endMoving();
}

void TRSprite::defreeze(){
    flgFreeze = false;
}

bool TRSprite::isFreezing(){
    return flgFreeze;
}

void TRSprite::move(){
    if (isMoving()) {
        setX(getX() + mVelX);
        if((getX() < 0) ||
           (getX() + getWidth() > levelRect->w)){
            setX(getX() - mVelX);
        }
        
        setY(getY() + mVelY);
        if((getY() < 0) ||
           (getY() + getHeight() > levelRect->h)){
            setY(getY() - mVelY);
        }
    }
}

void TRSprite::undo(){
    undoed = true;
    setX(getX() - mVelX);
    setY(getY() - mVelY);
}

void TRSprite::startMoving(){
    if(!flgFreeze && !flgMoving){
        for(int i = 0; i < 4; i++){
            if(isMovingAnimated()){
                mMovingAnimator[i]->reset();
            }
        }
        flgMoving = true;
    }
}

void TRSprite::endMoving(){
    for(int i = 0; i < 4; i++){
        if(isStaticAnimated()){
            mStaticAnimator[i]->reset();
        }
    }
    flgMoving = false;
}

bool TRSprite::isMoving(){
    return flgMoving;
}

void TRSprite::setStaticClip(SDL_Rect clipRect, TRDirection dir){
    mStaticClip[dir] = clipRect;
}

void TRSprite::render(){
    if (isMoving()) {
        if(isMovingAnimated()){
            mMovingAnimator[mDirection]->animate();
            setCurClip(mMovingAnimator[mDirection]->getCurrentClipRect());
        }else{
            setCurClip(mStaticClip[mDirection]);
        }
    }else{
        if (isStaticAnimated()) {
            mStaticAnimator[mDirection]->animate();
            setCurClip(mStaticAnimator[mDirection]->getCurrentClipRect());
        }else{
            setCurClip(mStaticClip[mDirection]);
        }
    }
    TRObject::render();
}