//
//  TREnemy.hpp
//  TombRaider
//
//  Created by 張正昊 on 13/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TREnemy_hpp
#define TREnemy_hpp

#include <stdio.h>
#include <queue>
#include "TRSprite.hpp"
#include "TRPathFinder.hpp"
#include "TRGrider.hpp"
#include "TRHero.hpp"

enum TREnemyType{
    TREnemyRandom = 0,
    TREnemySmart = 1
};

class TRHero;

class TREnemy : public TRSprite{
public:
    //属性
    void setHP(int nhp);
    void setDamage(int ndmg);
    void setArmor(int narm);
    void setSpeed(int nvel);
    int getHP();
    int getDamage();
    int getArmor();
    int getSpeed();
    
    //攻击
    void beAttacked(int dmg);
    void attack(TRHero* obj,int dmg);
    
    //移动
    void move();
    
    
    
private:
    int hp,dmg,arm,vel;
    
    //维护路径
    
    
    TRHero *hero;
    TRPathFinder *pathFinder;
    TRGrider *grider;
};

#endif /* TREnemy_hpp */
