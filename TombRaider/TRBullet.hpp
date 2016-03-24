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
#include "TRAnimator.hpp"

enum TRBulletType{
    TRBulletFriendly = 1,
    TRBulletHostile = 2
};

class TRHero;
class TREnemy;
class TRBullet : public TRSprite{
public:
    //构造器
    TRBullet();
    //属性
    int getSpeed();
    void setSpeed(int nvel);
    int getDamage();
    void setDamage(int ndmg);
    TRBulletType getType();
    void setType(TRBulletType ntype);
    //方向
    void setDirection(TRDirection ndir);
    //动画
    bool isAnimated();
    void setAnimated(bool aniflg);
    void setAnimator(TRAnimator *ani,TRDirection dir);
    void linkAnimator();
    //着弹
    void attackEnemy(TREnemy *obj);
    void attackHero(TRHero *obj);
    bool isUsed();
    //渲染
    void render();
    //移动
    void move();
private:
    TRBulletType type;
    bool animated;
    TRAnimator *animator[4];
    bool used;
    int dmg;
    int vel;
};

#endif /* TRBullet_hpp */
