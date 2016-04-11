//
//  TRItem.hpp
//  TombRaider
//
//  Created by 張正昊 on 18/3/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRItem_hpp
#define TRItem_hpp

#include <stdio.h>
#include <cmath>
#include "TRMapTile.hpp"
#include "TRHero.hpp"
#include "TRInterface.h"
//只要设定好对应的属性，使用的时候调用Activate()就可以了

enum TRItemType{
    TRItemBullet = 1,//子弹
    TRItemHeal = 2,//治疗
    TRItemKey = 3,//钥匙
    TRItemTreasure = 4,//财宝
    TRItemGun2 = 5
};

struct TRItem : public TRMapTile{
    TRItem(){
        setType(TRMapTileTypeGround);
        setPassBy(true);
    }
    TRItemType getItemType(){
        return type;
    }
    void activate(){
        switch (type) {
            case TRItemBullet:
                addbullet();
                break;

            case TRItemHeal:
                heal();
                break;

            case TRItemKey:
                hero->setGotTheKey(true);
                break;

            case TRItemTreasure:
                hero->setTreasure(hero->getTreasure()+1000+rand()%1000);
                break;

            default:
                break;
        }
    }

    void linkHero(TRHero *_hero){
        hero = _hero;
    }

    void render(){
        TRObject::render();
        if (mht() < MKRRANGE) {
            marker_texture -> render(getX() - camRect->x + 25, getY() - camRect->y + 25);
        }
    }

    void setItemType(TRItemType typ){
        type = typ;
    }

    TRHero *hero;
    TRInterface *interface;
    TRItemType type;
    TRTexture *marker_texture;

    //治疗道具相关
    int healval;
    void heal(){
        hero->heal(healval);
    }
    void setHealingValue(int det){
        healval = det;
    }

    //子弹道具相关
    int bulletval;
    int sandanNum;
    void addbullet(){
        hero->setBulletNum(hero->getBulletNum()+50+rand()%50);
    }
    void setBulletValue(int det){
        bulletval = det;
    }
    void addSandanNum(){
        hero->setSandanNum(hero->getSandanNum()+50+rand()%20);
    }
    void setSandanValue(int det){
        sandanNum = det;
    }

    //钥匙相关


    //宝藏相关



    static const int MKRRANGE = 80;
    int mht(){
        return abs(hero->getX() - this->getX()) + abs(hero->getY() - this->getY());
    }
};

#endif /* TRItem_hpp */
