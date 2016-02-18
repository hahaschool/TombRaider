//
//  TRObject.cpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRObject.hpp"

int TRObject::getX(){
    return mBox.x;
}

int TRObject::getY(){
    return mBox.y;
}

int TRObject::getWidth(){
    return mBox.w;
}

int TRObject::getHeight(){
    return mBox.h;
}

SDL_Rect TRObject::getBoxRect(){
    return mBox;
}

void TRObject::setX(int x){
    mBox.x = x;
}

void TRObject::setY(int y){
    mBox.y = y;
}

void TRObject::setWidth(int w){
    mBox.w = w;
}
void TRObject::setHeight(int h){
    mBox.h = h;
}

void TRObject::setBoxRect(SDL_Rect newBox){
    mBox = newBox;
}

void TRObject::setPos(int x,int y){
    setX(x),setY(y);
}

void TRObject::setCurClip(SDL_Rect clipRect){
    curClip = clipRect;
}

void TRObject::linkLevelRect(SDL_Rect* lvlrect){
    levelRect = lvlrect;
}
void TRObject::linkCameraRect(SDL_Rect* camrect){
    camRect = camrect;
}

void TRObject::render(){
    mTexture->render(getX() - camRect->x, getY() - camRect->y, &curClip);
}

void TRObject::linkTexture(TRTexture *texture){
    mTexture = texture;
}
