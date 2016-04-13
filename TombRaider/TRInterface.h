#ifndef TRINTERFACE_H_INCLUDED
#define TRINTERFACE_H_INCLUDED
#include "TRTexture.hpp"
#include "TRHero.hpp"
enum TRInterfaceType{
    TRInterfaceTypeHp = 1,
    TRInterfaceTypeTreasure = 2,
    TRInterfaceTypeGanlanzhi = 3,
    TRInterfaceTypeBullet = 4,
    TRInterfaceTypeKey = 5,
    TRInterfaceTypeLowspeed = 6,
    TRInterfaceTypeGUN2 = 7
};
class TRInterface{
public:
    TRInterface();
    //属性
    int getMaxHp();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    int getTreasure();
    int getTheNumOfBullets();
    TRInterfaceType getInterfaceType();
    bool haveGotTheKey();

    void setInterfaceType(TRInterfaceType type);

    void setX(int x);
    void setY(int y);
    void setWidth(int w);
    void setHeight(int h);
    void setTreasure(int treasure);
    void setGotTheKey(bool got);
    void setNumOfBullets(int bulletsnum);

    SDL_Rect getBoxRect();
    void setBoxRect(SDL_Rect newBox);
    void setPos(int x,int y);

    void setCurClip(SDL_Rect clipRect);
    void linkTexture(TRTexture *texture);
    TRTexture getTexture();

    void render();
private:
    SDL_Rect mBox;
    SDL_Rect curClip;
    SDL_Rect hpRect;
    SDL_Rect treasureRect;
    SDL_Rect keyRect;
    SDL_Rect bulletRect;
    int Hp;
    int treasureNum;
    int bulletNum;
    bool haveGot;

    TRHero* hero;
    TRTexture* mTexture;

    TRInterfaceType interfaceType;
};

#endif // TREQUIPMENT_H_INCLUDED
