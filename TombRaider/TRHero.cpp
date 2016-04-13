//
//  TRHero.cpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRHero.hpp"

TRHero::TRHero(){
    const int INF = 0x3f3f3f3f;
    isFiring = false;
    anilock = false;
    anilockrem = 0;
    atk_cd = atk_cd_rem = 0;
    fire_cd = 0;
    bullet_cd = bullet_cd_rem = 10;
    alive = true;
    attacking = false;
    standingAnimated = false;
    walkingAnimated = false;
    attackingAnimated = false;
    firingAnimated = false;
    flgdebuff_slow = false;
    debuff_slow_dmg = debuff_slow_rem = 0;
    flgdebuff_bleed = false;
    debuff_bleed_dmg = debuff_bleed_rem = 0;
    flgdebuff_freeze = false;
    flgdebuff_nogun = false;
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

void TRHero::setTreasure(int treasure){
    trea = treasure;
}

void TRHero::setBulletNum(int bullet){
    bulletNum = bullet;
}

void TRHero::setGotTheKey(bool haveGot)
{
    got = haveGot;
}

bool TRHero::getGotTheKey()
{
    return got;
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

int TRHero::getTreasure(){
    return trea;
}

int TRHero::getBulletNum(){
    return bulletNum;
}

void TRHero::setZnum(int bigNum){
    zNum = bigNum;
}

int TRHero::getZnum()
{
    return zNum;
}

int TRHero::getSandanNum(){
    return sandanNum;
}

void TRHero::setSandanNum(int sandan){
    sandanNum = sandan;
}

#pragma mark - 死亡

void TRHero::setDeathClip(SDL_Rect clipRect,TRDirection dir){
    deathRect[dir] = clipRect;
}

void TRHero::goDie(){
    setStaticAnimated(false);
    freeze();
    setStaticClip(deathRect[TRDirectionUp], TRDirectionUp);
    setStaticClip(deathRect[TRDirectionDown], TRDirectionDown);
    setStaticClip(deathRect[TRDirectionLeft], TRDirectionLeft);
    setStaticClip(deathRect[TRDirectionRight], TRDirectionRight);
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

bool TRHero::performAttack(){
    if(!flgdebuff_freeze && atk_cd_rem <= 0 && zNum > 0){
        if(isAttackingAnimated()){
            linkAttackingAnimator();
            lock(atk_cd);
        }
        atk_cd_rem = atk_cd;
        attacking = true;
        return true;
    }
    return false;
}

void TRHero::endAttack(){
    linkStandingAnimator();
    unlock();
    attacking = false;
}

void TRHero::attack(TREnemy *obj){
    obj->beAttacked(dmg);
}

void TRHero::setAttackCD(int ncd){
    atk_cd = ncd;
}

int TRHero::getAttackCD(){
    return atk_cd;
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

int TRHero::getDebuffSlow(){
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
void TRHero::fire(){
    if(!flgdebuff_nogun && bullet_cd_rem <= 0 && bulletNum > 0){
        isFiring = true;
        bullet_cd_rem = bullet_cd;
        bulletNum--;
    }
}

bool TRHero::willFire(){
    return isFiring;
}

void TRHero::fireDone(){
    isFiring = false;
}

void TRHero::setBulletKey(std::string key){
    bul_key = key;
}

std::string TRHero::getBulletKey(){
    return bul_key;
}



#pragma mark - 移动
void TRHero::startMoveUp(){
    if (!isMoving()) {
        linkWalkingAnimator();
        startMoving();
    }
    setDirection(TRDirectionUp);
    setVelX(0);
    setVelY(-vel);
}

void TRHero::startMoveLeft(){
    if (!isMoving()) {
        linkWalkingAnimator();
        startMoving();
    }
    setDirection(TRDirectionLeft);
    setVelX(-vel);
    setVelY(0);
}

void TRHero::startMoveDown(){
    if (!isMoving()) {
        linkWalkingAnimator();
        startMoving();
    }
    setDirection(TRDirectionDown);
    setVelX(0);
    setVelY(vel);
}

void TRHero::startMoveRight(){
    if (!isMoving()) {
        linkWalkingAnimator();
        startMoving();
    }
    setDirection(TRDirectionRight);
    setVelX(vel);
    setVelY(0);
}

void TRHero::endMoving(){
    setVelXY(0);
    TRSprite::endMoving();
}

void TRHero::move(){
    if(anilock){
        if(anilockrem-- <= 0){
            endAttack();
        }
    }
    atk_cd_rem--,bullet_cd_rem--;
    if (atk_cd_rem < 0) {
        atk_cd_rem = 0;
    }
    if(bullet_cd_rem < 0){
        bullet_cd_rem = 0;
    }
    if(is_debuff_Bleed()){
        debuff_bleed_rem--;
        setHP(getHP() - debuff_bleed_dmg);
        if (debuff_bleed_rem <= 0) {
            debuff_Bleed_clear();
        }
        if(getHP() < 0) goDie(),debuff_Bleed_clear();
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
    if (isMoving()) {
        TRSprite::move();
    }
}

#pragma mark - 渲染
void TRHero::render(){
    TRSprite::render();
}

#pragma mark - 治疗
void TRHero::heal(int det){
    setHP(std::min(getMaxHP(),getHP()+det));
}

#pragma mark - 动画
#pragma mark 站立
void TRHero::setStandingAnimator(TRAnimator *ani, TRDirection dir){
    standingAnimator[dir] = ani;
}

void TRHero::linkStandingAnimator(){
    if(isStandingAnimated()){
        setStaticAnimated(true);
        linkStaticAnimator(standingAnimator[TRDirectionUp], TRDirectionUp);
        linkStaticAnimator(standingAnimator[TRDirectionLeft], TRDirectionLeft);
        linkStaticAnimator(standingAnimator[TRDirectionRight], TRDirectionRight);
        linkStaticAnimator(standingAnimator[TRDirectionDown], TRDirectionDown);
    }else{
        setStaticAnimated(false);
    }
}

void TRHero::setStandingAnimated(bool flg){
    standingAnimated = flg;
}

bool TRHero::isStandingAnimated(){
    return standingAnimated;
}
#pragma mark 走动
void TRHero::setWalkingAnimator(TRAnimator *ani, TRDirection dir){
    walkingAnimator[dir] = ani;
}

void TRHero::linkWalkingAnimator(){
    if(isWalkingAnimated()){
        setMovingAnimated(true);
        linkMovingAnimator(walkingAnimator[TRDirectionUp], TRDirectionUp);
        linkMovingAnimator(walkingAnimator[TRDirectionLeft], TRDirectionLeft);
        linkMovingAnimator(walkingAnimator[TRDirectionRight], TRDirectionRight);
        linkMovingAnimator(walkingAnimator[TRDirectionDown], TRDirectionDown);
    }else{
        setMovingAnimated(false);
    }
}

void TRHero::setWalkingAnimated(bool flg){
    walkingAnimated = flg;
}

bool TRHero::isWalkingAnimated(){
    return walkingAnimated;
}
#pragma mark 近身攻击
void TRHero::setAttackingAnimator(TRAnimator *ani, TRDirection dir){
    attackingAnimator[dir] = ani;
}

void TRHero::linkAttackingAnimator(){
    if(isAttackingAnimated()){
        setStaticAnimated(true);
        linkStaticAnimator(attackingAnimator[TRDirectionUp], TRDirectionUp);
        linkStaticAnimator(attackingAnimator[TRDirectionLeft], TRDirectionLeft);
        linkStaticAnimator(attackingAnimator[TRDirectionRight], TRDirectionRight);
        linkStaticAnimator(attackingAnimator[TRDirectionDown], TRDirectionDown);
    }else{
        setStaticAnimated(false);
    }
}

void TRHero::setAttackingAnimated(bool flg){
    attackingAnimated = flg;
}

bool TRHero::isAttackingAnimated(){
    return attackingAnimated;
}
#pragma mark 远程攻击
void TRHero::setFiringAnimator(TRAnimator *ani, TRDirection dir){
    firingAnimator[dir] = ani;
}

void TRHero::linkFiringAnimator(){
    if(isFiringAnimated()){
        setStaticAnimated(true);
        linkStaticAnimator(firingAnimator[TRDirectionUp], TRDirectionUp);
        linkStaticAnimator(firingAnimator[TRDirectionLeft], TRDirectionLeft);
        linkStaticAnimator(firingAnimator[TRDirectionRight], TRDirectionRight);
        linkStaticAnimator(firingAnimator[TRDirectionDown], TRDirectionDown);
    }else{
        setStaticAnimated(false);
    }
}

void TRHero::setFiringAnimated(bool flg){
    firingAnimated = flg;
}

bool TRHero::isFiringAnimated(){
    return firingAnimated;
}

#pragma mark - 攻击范围
#pragma mark 设定攻击范围扩张系数
void TRHero::setAttackRangeFactor(double atkf){
    atkFactor = atkf;
}
#pragma mark 得到攻击范围
SDL_Rect TRHero::getAttackRect(){
    SDL_Rect ret = getBoxRect();
    if (getDirection() == TRDirectionUp) {
        ret.y -= getHeight()*atkFactor;
        ret.h += getHeight()*atkFactor;
    }else if(getDirection() == TRDirectionRight){
        ret.w += getWidth()*atkFactor;
    }else if(getDirection() == TRDirectionDown){
        ret.h += getHeight()*atkFactor;
    }else if(getDirection() == TRDirectionLeft){
        ret.x -= getWidth()*atkFactor;
        ret.w += getWidth()*atkFactor;
    }
    return ret;
}



#pragma mark - Animator Lockdown (PRIVATE)
void TRHero::lock(int interval){
    freeze();
    anilockrem = interval;
    anilock = true;
}
void TRHero::unlock(){
    defreeze();
    anilock = false;
    anilockrem = 0;
}
