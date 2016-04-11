#include "TRInterface.h"
TRInterface::TRInterface(){
}

int TRInterface::getX(){
   return mBox.x;
}

int TRInterface::getY(){
   return mBox.y;
}

int TRInterface::getWidth(){
   return mBox.w;
}

int TRInterface::getHeight(){
   return mBox.h;
}

SDL_Rect TRInterface::getBoxRect(){
   return mBox;
}

void TRInterface::setX(int x){
   mBox.x = x;
}

void TRInterface::setY(int y){
   mBox.y = y;
}

void TRInterface::setWidth(int w){
   mBox.w = w;
}

void TRInterface::setHeight(int h){
   mBox.h = h;
}

void TRInterface::setBoxRect(SDL_Rect newBox){
   mBox = newBox;
}

void TRInterface::setCurClip(SDL_Rect clipRect){
   curClip = clipRect;
}

int TRInterface::getTreasure(){
   return treasureNum = hero->getTreasure();
}

bool TRInterface::haveGotTheKey(){
   return haveGot;
}

int TRInterface::getTheNumOfBullets(){
   return bulletNum;
}

void TRInterface::setGotTheKey(bool got)
{
    haveGot = got;
}

void TRInterface::setNumOfBullets(int bulletnum)
{
    bulletNum = bulletnum;
}

void TRInterface::setTreasure(int treasure)
{
    treasureNum = treasure;
}

void TRInterface::render()
{
    switch(interfaceType){
case TRInterfaceTypeHp:
    //setCurClip(hpRect);
    break;
case TRInterfaceTypeTreasure:
    //setCurClip(treasureRect);
    break;
case TRInterfaceTypeGanlanzhi:
    //setCurClip(ganlanzhiRect);
    break;
case TRInterfaceTypeBullet:
    //setCurClip(bulletRect);
    break;
case TRInterfaceTypeKey:
    if(haveGot){
    //setCurClip(keyRect);
    }
    break;
    }
    mTexture->render(getX(),getY(),&curClip);
}

void TRInterface::setInterfaceType(TRInterfaceType type){
    interfaceType = type;
}

TRInterfaceType TRInterface::getInterfaceType(){
    return interfaceType;
}

void TRInterface::linkTexture(TRTexture *texture)
{
    mTexture = texture;
}
