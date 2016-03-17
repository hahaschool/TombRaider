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

//只要设定好对应的属性，使用的时候调用Activate()就可以了

enum TRItemType{
    TRItemBullet = 1,//子弹
    TRItemHeal = 2,//治疗
    TRItemKey = 3,//钥匙
    TRItemTreasure = 4//财宝
};

struct TRItem : public TRMapTile{
    void activate(){
        switch (type) {
            case TRItemBullet:
                addbullet();
                break;
                
            case TRItemHeal:
                heal();
                break;
                
            case TRItemKey:
                
                break;
                
            case TRItemTreasure:
                
                break;
                
            default:
                break;
        }
    }
    
    void linkHero(TRHero *_hero){
        hero = _hero;
    }
    
    void render(){
        if (mht() < MKRRANGE) {
            marker_texture -> render(getX() + 25, getY() + 25);
        }
        TRObject::render();
    }
    

    TRHero *hero;
    TRItemType type;
    TRTexture *marker_texture;
    
    //治疗道具相关
    int healval;
    void heal(){
        hero->heal(healval);
    }
    
    //子弹道具相关
    int bulletval;
    void addbullet(){
        
    }
    
    //钥匙相关
    
    
    //宝藏相关
    
    
    
    static const int MKRRANGE = 2;
    int mht(){
        return abs(hero->getX() - this->getX()) + abs(hero->getY() - this->getY());
    }
};

#endif /* TRItem_hpp */
