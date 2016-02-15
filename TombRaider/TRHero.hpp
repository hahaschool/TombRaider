//
//  TRHero.hpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRHero_hpp
#define TRHero_hpp

#include <stdio.h>
#include "TRSprite.hpp"
#include "TREnemy.hpp"
#include "TRBullet.hpp"
/*
 使用说明:
 1.配置血量，最大血量，正常移动速度，防御力，近身攻击力，子弹攻击力，子弹速度
 2.配置动画信息（行走动画，站立动画，治疗动画，近身攻击，远程攻击）
 3.通过isAlive()判断是否还活着
 4.通过canFire()判断是否可以射击，通过fire()进行射击动画，返回TRBullet*
 5.通过performAttack()进行近身攻击动画，attack()实际攻击对象
 6.通过heal()进行治疗动画并治疗
 7.debuff开头的函数用来维护不良状态
 8.通过四个startMoving()接收开始移动信号，每一帧调用move()进行实际移动
 9.render()是渲染时函数
*/
class TRHero : public TRSprite{
public:
    //属性
    TRHero();
    void setMaxHP(int nmxhp);
    void setHP(int nhp);
    void setVelocity(int nvel);
    void setArmour(int narm);
    void setDamage(int ndmg);
    int getMaxHP();
    int getHP();
    int getVelocity();
    int getArmour();
    int getDamage();
    //死亡
    void goDie();
    
    //不良状态
    void debuff_Slow(int interval,int dmg);
    void debuff_Bleed(int interval,int dmg);
    void debuff_Freeze(int interval);
    void debuff_Nogun(int interval);
    void debuff_Slow_clear();
    void debuff_Bleed_clear();
    void debuff_Freeze_clear();
    void debuff_Nogun_clear();
    void debuff_clear();
    bool is_debuff_Slow();
    int dmg_debuff_Slow();
    int rem_debuff_Slow();
    bool is_debuff_Bleed();
    int dmg_debuff_Bleed();
    int rem_debuff_Bleed();
    bool is_debuff_Freeze();
    int rem_debuff_Freeze();
    bool is_debuff_Nogun();
    int rem_debuff_Nogun();
    
    //开枪
    TRBullet* fire();
    void setBulletDamage(int dmg);
    int getBulletDamage();
    void setBulletSpeed(int nvel);
    int getBulletSpeed();
    
    //移动
    void startMoveUp();
    void startMoveDown();
    void startMoveLeft();
    void startMoveRight();
    void endMoving();
    void move();
    //被攻击
    void beAttacked(int dmg);
    //近身攻击
    void performAttack();
    void attack(TREnemy &obj);
    //治疗
    void heal(int det);
    
    //设定动画
    void setAttackingAnimator(TRAnimator *ani,TRDirection dir);
    void setWalkingAnimator(TRAnimator *ani,TRDirection dir);
    void setStandingAnimator(TRAnimator *ani,TRDirection dir);
    void setHealingAnimator(TRAnimator *ani,TRDirection dir);
    void setFiringAnimator(TRAnimator *ani,TRDirection dir);
    void setStandingAnimated();
    bool isStandingAnimated();
    bool isAttackingAnimated();
    bool isWalkingAnimated();
    bool isFiringAnimated();
    
    
    //渲染时函数，用来在每一帧确认状态
    void render();
    
private:
    //cool down
    int atk_cd;
    int fire_cd;
    int bullet_cd;
    
    //property
    int hp,mxhp,arm,dmg;
    int vel;
    
    //status
    bool alive;
    bool attacking;
    
    //animator
    bool standingAnimated;
    TRAnimator *attackAnimator[4];
    TRAnimator *standingAnimator[4];
    TRAnimator *walkingAnimator[4];
    
    //debuffs
    bool flgdebuff_slow;
    int debuff_slow_dmg;
    int debuff_slow_rem;
    bool flgdebuff_bleed;
    int debuff_bleed_dmg;
    int debuff_bleed_rem;
    bool flgdebuff_freeze;
    int debuff_freeze_rem;
    bool flgdebuff_nogun;
    int debuff_nogun_rem;
    
    //gun
    int bullet_dmg;
    int bullet_vel;
    
};

#endif /* TRHero_hpp */
