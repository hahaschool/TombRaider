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
#include <algorithm>
#include "TRSprite.hpp"
#include "TRPathFinder.hpp"
#include "TRGrider.hpp"
#include "TRHero.hpp"

/*
 使用说明：
 1.配置好属性，贴图
 2.使用isAlive()确认死活
 3.攻击时，调用startAttack()激活动画,返回的是这一轮能不能攻击，攻击结束后自动回复走动状态
 
 */

enum TREnemyType{
    TREnemyRandom = 0,
    TREnemySmart = 1
};

class TRHero;

class TREnemy : public TRSprite{
public:
    //贴图和动画配置
    bool isWalkingAnimated();
    void setWalkingAnimated(bool flg);
    void setWalkingAnimator(TRAnimator *ani,TRDirection dir);
    void linkWalkingAnimator();
    bool isAttackingAnimated();
    void setAttackingAnimated(bool flg);
    void setAttackingAnimator(TRAnimator *ani,TRDirection dir);
    void linkAttackingAnimator();
    void setDeathClip(SDL_Rect clipRect,TRDirection dir);
    
    //属性
    void setType(TREnemyType ntype);
    void setHP(int nhp);
    void setDamage(int ndmg);
    void setArmour(int narm);
    void setSpeed(int nvel);
    void setAttackCD(int ncd);
    TREnemyType getType();
    int getHP();
    int getDamage();
    int getArmor();
    int getSpeed();
    int getAttackCD();
    
    //死亡
    void goDie();
    bool isAlive();
    
    //攻击
    void beAttacked(int dmg);
    void attack(TRHero* obj,int dmg);
    bool startAttacking();
    void endAttacking();
    
    //移动
    void startMoving();
    void endMoving();
    void moveRandom();
    void moveAlongPath();
    void move();
    
    //维护路径
    void clearRoute();
    void planRoute(bool force);
    
    
    //链接英雄单位,辅助对象
    void linkHero(TRHero *nhero);
    void linkGrider(TRGrider *ngrider);
    void linkPathFinder(TRPathFinder *npathfinder);
    
    //渲染函数
    void render();
    
    
private:
    TREnemyType type;
    
    //animator lock
    bool anilock;
    int anilockrem;
    void lock(int interval);
    void unlock();
    
    int atk_cd;
    int atk_cd_rem;
    
    int hp,dmg,arm,vel;
    bool alive;
    bool chasing;
    
    int prv_hero_x,prv_hero_y;
    
    //贴图
    SDL_Rect deathClip[4];
    bool walkingAnimated;
    TRAnimator *walkingAnimator[4];
    bool attackingAnimated;
    TRAnimator *attackingAnimator[4];
    
    
    //维护路径
    std::queue<std::pair<int,int> > path;
    
    TRHero *hero;
    TRPathFinder *pathFinder;
    TRGrider *grider;
};

#endif /* TREnemy_hpp */
