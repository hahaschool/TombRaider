//
//  TRBullet.hpp
//  TombRaider
//
//  Created by 張正昊 on 15/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRBullet_hpp
#define TRBullet_hpp

#include "TRSprite.hpp"
#include "TRHero.hpp"
#include "TRSprite.hpp"

enum TRBulletType{
    TRBulletFriendly = 1,
    TRBulletHostile = 2
};

class TRHero;
class TREnemy;
class TRBullet : public TRSprite{
public:
    //属性
    int getSpeed();
    void setSpeed(int nvel);
    int getDamage();
    void setDamage(int ndmg);
    TRBulletType getType();
    void setType(TRBulletType ntype);
    //方向
    void setDirection(TRDirection ndir);
    //着弹
    void attackEnemy(TREnemy *obj);
    void attackHero(TRHero *obj);
    bool isUsed();
    //渲染
    void render();
private:
    TRBulletType type;
    bool used;
    int dmg;
    int vel;
};

#endif /* TRBullet_hpp */
