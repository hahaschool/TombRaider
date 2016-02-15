//
//  TRHero.cpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRHero.hpp"

TRHero::TRHero(){
    hp = mxhp = arm = vel = 0;
    alive = true;
    attacking = false;
    standingAnimated = false;
    flgdebuff_bleed = false;
    flgdebuff_slow = false;
    flgdebuff_nogun = false;
    flgdebuff_freeze = false;
}

#pragma mark - 属性

void TRHero::setMaxHP(int nmxhp){
    mxhp = nmxhp;
}

void TRHero::setHP(int nhp){
    hp = nhp;
}
void TRHero::setVelocity(int nvel){
    vel = nvel;
}

void TRHero::setArmour(int narm){
    arm = narm;
}

void TRHero::setDamage(int ndmg){
    dmg = ndmg;
}

int TRHero::getMaxHP(){
    return mxhp;
}

int TRHero::getHP(){
    return hp;
}

int TRHero::getVelocity(){
    return vel;
}

int TRHero::getArmour(){
    return arm;
}

int TRHero::getDamage(){
    return dmg;
}

#pragma mark - 死亡

void TRHero::goDie(){
    setStaticAnimated(false);
    freeze();
    setStaticClip(SDL_Rect(), TRDirectionUp);
    setStaticClip(SDL_Rect(), TRDirectionDown);
    setStaticClip(SDL_Rect(), TRDirectionLeft);
    setStaticClip(SDL_Rect(), TRDirectionRight);
    alive = false;
}

#pragma mark - 被弹

void TRHero::beAttacked(int dmg){
    if(arm < dmg){
        hp -= dmg - arm;
    }
    if(hp <= 0){
        hp = 0;
        goDie();
    }
}

#pragma mark - 攻击

void TRHero::performAttack(){
    if(isAttackingAnimated()){
        setStaticAnimated(true);
        linkStaticAnimator(attackAnimator[TRDirectionUp], TRDirectionUp);
        linkStaticAnimator(attackAnimator[TRDirectionLeft], TRDirectionLeft);
        linkStaticAnimator(attackAnimator[TRDirectionRight], TRDirectionRight);
        linkStaticAnimator(attackAnimator[TRDirectionDown], TRDirectionDown);
        atkfrmcnt = attackAnimator[0]->getAnimationPeriod();
        freeze();
    }
}

void TRHero::attack(TREnemy &obj){
    obj.beAttacked(dmg);
}

#pragma mark - 不良状态
#pragma mark 减速
//不良状态
void TRHero::debuff_Slow(int interval,int dmg){
    debuff_Slow_clear();
    debuff_slow_rem = interval;
    debuff_slow_dmg = dmg;
    vel -= dmg;
    flgdebuff_slow = true;
}

void TRHero::debuff_Slow_clear(){
    flgdebuff_slow = false;
    vel += debuff_slow_dmg;
    debuff_slow_dmg = 0;
}

bool TRHero::is_debuff_Slow(){
    return flgdebuff_slow;
}

int TRHero::dmg_debuff_Slow(){
    return debuff_slow_dmg;
}

int TRHero::rem_debuff_Slow(){
    return debuff_slow_rem;
}

#pragma mark 出血

void TRHero::debuff_Bleed(int interval,int dmg){
    debuff_Bleed_clear();
    debuff_bleed_rem = interval;
    debuff_bleed_dmg = dmg;
    flgdebuff_bleed = true;
}

void TRHero::debuff_Bleed_clear(){
    flgdebuff_bleed = false;
}

bool TRHero::is_debuff_Bleed(){
    return flgdebuff_bleed;
}

int TRHero::dmg_debuff_Bleed(){
    return debuff_bleed_dmg;
}

int TRHero::rem_debuff_Bleed(){
    return debuff_bleed_rem;
}

#pragma mark 冻结（无法移动）

void TRHero::debuff_Freeze(int interval){
    debuff_freeze_rem = interval;
    flgdebuff_freeze = true;
    freeze();
}

void TRHero::debuff_Freeze_clear(){
    flgdebuff_freeze = false;
    defreeze();
}

bool TRHero::is_debuff_Freeze(){
    return flgdebuff_freeze;
}

int TRHero::rem_debuff_Freeze(){
    return debuff_freeze_rem;
}

#pragma mark 缴械（无法远程攻击）

void TRHero::debuff_Nogun(int interval){
    debuff_nogun_rem = interval;
    flgdebuff_nogun = true;
}

void TRHero::debuff_Nogun_clear(){
    flgdebuff_nogun = false;
}

bool TRHero::is_debuff_Nogun(){
    return flgdebuff_nogun;
}

int TRHero::rem_debuff_Nogun(){
    return debuff_nogun_rem;
}

#pragma mark 消除全部不良状态

void TRHero::debuff_clear(){
    debuff_Slow_clear();
    debuff_Nogun_clear();
    debuff_Bleed_clear();
    debuff_Freeze_clear();
}

#pragma mark - 远程攻击
TRBullet* TRHero::fire(){
    
}

void TRHero::setBulletDamage(int ndmg){
    bullet_dmg = ndmg;
}

int TRHero::getBulletDamage(){
    return bullet_dmg;
}

void TRHero::setBulletSpeed(int nvel){
    bullet_vel = nvel;
}

int TRHero::getBulletSpeed(){
    return bullet_vel;
}

#pragma mark - 移动
void TRHero::startMoveUp(){
    startMoving();
    setDirection(TRDirectionUp);
    setVelX(0);
    setVelY(-vel);
}

void TRHero::startMoveLeft(){
    startMoving();
    setDirection(TRDirectionLeft);
    setVelX(-vel);
    setVelY(0);
}

void TRHero::startMoveDown(){
    startMoving();
    setDirection(TRDirectionDown);
    setVelX(0);
    setVelY(vel);
}

void TRHero::startMoveRight(){
    startMoving();
    setDirection(TRDirectionRight);
    setVelX(vel);
    setVelY(0);
}

void TRHero::endMoving(){
    setVelXY(0);
    TRSprite::endMoving();
}

void TRHero::move(){
    if (isMoving()) {
        TRSprite::move();
    }
}

#pragma mark - 渲染
void TRHero::render(){
    atk_cd--,fire_cd--,bullet_cd--;
    
    if(is_debuff_Bleed()){
        debuff_bleed_rem--;
        setHP(getHP() - debuff_bleed_dmg);
        if (debuff_bleed_rem <= 0) {
            debuff_Bleed_clear();
        }
    }
    if(is_debuff_Freeze()){
        freeze();
        debuff_freeze_rem--;
        if(debuff_freeze_rem <= 0){
            debuff_Freeze_clear();
        }
    }
    if(is_debuff_Nogun()){
        debuff_nogun_rem--;
        if (debuff_nogun_rem <= 0) {
            debuff_Nogun_clear();
        }
    }
    if(is_debuff_Slow()){
        debuff_slow_rem--;
        if(debuff_slow_rem <= 0){
            debuff_Slow_clear();
        }
    }
    
    TRSprite::render();
}

#pragma mark - 治疗
void TRHero::heal(int det){
    setHP(std::max(getMaxHP(),getHP()+det));
}