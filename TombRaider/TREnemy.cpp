//
//  TREnemy.cpp
//  TombRaider
//
//  Created by 張正昊 on 13/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TREnemy.hpp"

#pragma mark - 贴图和动画配置
bool TREnemy::isWalkingAnimated(){
    return walkingAnimated;
}

void TREnemy::setWalkingAnimated(bool flg){
    walkingAnimated = flg;
    if(!flg){
        setMovingAnimated(false);
    }
}

void TREnemy::setWalkingAnimator(TRAnimator *ani,TRDirection dir){
    walkingAnimator[dir] = ani;
}

void TREnemy::linkWalkingAnimator(){
    if(isWalkingAnimated()){
        setMovingAnimated(true);
        linkMovingAnimator(walkingAnimator[TRDirectionUp], TRDirectionUp);
        linkMovingAnimator(walkingAnimator[TRDirectionLeft], TRDirectionLeft);
        linkMovingAnimator(walkingAnimator[TRDirectionDown], TRDirectionDown);
        linkMovingAnimator(walkingAnimator[TRDirectionRight], TRDirectionRight);
    }else{
        setMovingAnimated(false);
    }
}

bool TREnemy::isAttackingAnimated(){
    return attackingAnimated;
}

void TREnemy::setAttackingAnimated(bool flg){
    attackingAnimated = flg;
}

void TREnemy::setAttackingAnimator(TRAnimator *ani,TRDirection dir){
    attackingAnimator[dir] = ani;
}

void TREnemy::linkAttackingAnimator(){
    if (attackingAnimated) {
        setStaticAnimated(true);
        linkStaticAnimator(walkingAnimator[TRDirectionUp], TRDirectionUp);
        linkStaticAnimator(walkingAnimator[TRDirectionLeft], TRDirectionLeft);
        linkStaticAnimator(walkingAnimator[TRDirectionDown], TRDirectionDown);
        linkStaticAnimator(walkingAnimator[TRDirectionRight], TRDirectionRight);
    }else{
        setStaticAnimated(false);
    }
}

void TREnemy::setDeathClip(SDL_Rect clipRect,TRDirection dir){
    deathClip[dir] = clipRect;
}



#pragma mark - 属性
void TREnemy::setType(TREnemyType ntype){
    type = ntype;
}

TREnemyType TREnemy::getType(){
    return type;
}

void TREnemy::setHP(int nhp){
    hp = nhp;
}

void TREnemy::setDamage(int ndmg){
    dmg = ndmg;
}

void TREnemy::setArmour(int narm){
    arm = narm;
}

void TREnemy::setSpeed(int nvel){
    vel = nvel;
}

void TREnemy::setAttackCD(int ncd){
    atk_cd = ncd;
}

int TREnemy::getHP(){
    return hp;
}

int TREnemy::getArmor(){
    return arm;
}

int TREnemy::getSpeed(){
    return vel;
}

int TREnemy::getDamage(){
    return dmg;
}
int TREnemy::getAttackCD(){
    return atk_cd;
}

#pragma mark - 死亡

void TREnemy::goDie(){
    setStaticAnimated(false);
    freeze();
    setStaticClip(deathClip[TRDirectionUp], TRDirectionUp);
    setStaticClip(deathClip[TRDirectionDown], TRDirectionDown);
    setStaticClip(deathClip[TRDirectionLeft], TRDirectionLeft);
    setStaticClip(deathClip[TRDirectionRight], TRDirectionRight);
    alive = false;
}

bool TREnemy::isAlive(){
    return alive;
}

#pragma mark - 被弹
void TREnemy::beAttacked(int dmg){
    if(arm < dmg){
        hp -= dmg - arm;
        if(hp <= 0){
            goDie();
        }
    }
    
}

#pragma mark - 攻击
bool TREnemy::startAttacking(){
    if(atk_cd_rem <= 0){
        atk_cd_rem = atk_cd;
        if(isAttackingAnimated()){
            linkAttackingAnimator();
            endMoving();
            lock(atk_cd);
        }
        return true;
    }
    return false;
}

void TREnemy::endAttacking(){
    setStaticAnimated(false);
    startMoving();
}

void TREnemy::attack(TRHero *obj, int dmg){
    obj->beAttacked(dmg);
}

#pragma mark - 渲染
void TREnemy::render(){
    if(anilock){
        anilockrem--;
        if(anilockrem <= 0){
            unlock();
            endAttacking();
        }
    }
    atk_cd_rem--;
    move();
    TRSprite::render();
}

#pragma mark - 连接辅助对象

void TREnemy::linkHero(TRHero *nhero){
    hero = nhero;
}

void TREnemy::linkGrider(TRGrider *ngrider){
    grider = ngrider;
}

void TREnemy::linkPathFinder(TRPathFinder *npathfinder){
    pathFinder = npathfinder;
}

#pragma mark - 维护路径

void TREnemy::clearRoute(){
    while(!path.empty()){
        path.pop();
    }
}

void TREnemy::planRoute(bool force){
    int hero_gridX,hero_gridY,gridX,gridY;
    grider->convertLevelTopLeftToGrid(getX(), getY(), gridX, gridY);
    grider->convertLevelTopLeftToGrid(hero->getX(), hero->getY(), hero_gridX, hero_gridY);
    if(force || hero_gridX != prv_hero_x || hero_gridY != prv_hero_y){
        pathFinder->setStartingPoint(gridX, gridY);
        pathFinder->setTargetPoint(hero_gridX, hero_gridY);
        pathFinder->findPath();
        clearRoute();
        int tx,ty,ax,ay;
        while(pathFinder->extractPath(tx, ty)){
            grider->convertGridToLevelTopLeft(tx, ty, ax, ay);
            path.push(std::make_pair(ax,ay));
        }
    }
}

#pragma mark - 移动

void TREnemy::move(){
    if (isMoving()) {
        if(type == TREnemyRandom){
            moveRandom();
        }else if(type == TREnemySmart){
            moveAlongPath();
        }
    }
}

void TREnemy::moveAlongPath(){
    if(path.empty()){
        return;
    }
    int topX = path.front().first;
    int topY = path.front().second;
    int curX = getX();
    int curY = getY();
    if(curX != topX){
        if(std::abs(curX - topX) < vel){
            if(curX > topX){
                setDirection(TRDirectionLeft);
                curX = topX;
            }else{
                setDirection(TRDirectionRight);
                curX = topX;
            }
        }else{
            if (curX > topX) {
                setDirection(TRDirectionLeft);
                curX -= vel;
            }else{
                setDirection(TRDirectionRight);
                curX += vel;
            }
        }
        if(curX == topX && curY == topY){
            path.pop();
        }
        return;
    }
    if(curY != topY){
        if(std::abs(curY - topY) < vel){
            if(curY > topY){
                setDirection(TRDirectionUp);
                curY = topY;
            }else{
                setDirection(TRDirectionDown);
                curY = topY;
            }
        }else{
            if (curY > topY) {
                setDirection(TRDirectionUp);
                curY -= vel;
            }else{
                setDirection(TRDirectionDown);
                curY += vel;
            }
        }
        if(curX == topX && curY == topY){
            path.pop();
        }
        return;
    }
}

void TREnemy::moveRandom(){
    int curdir = rand()%4;
    setDirection(curdir);
    if(curdir == TRDirectionUp){
        setVelY(-vel);
        setVelX(0);
    }else if(curdir == TRDirectionLeft){
        setVelX(-vel);
        setVelY(0);
    }else if(curdir == TRDirectionRight){
        setVelX(vel);
        setVelY(0);
    }else{
        setVelX(0);
        setVelY(vel);
    }
    TRSprite::move();
}

void TREnemy::startMoving(){
    linkWalkingAnimator();
    TRSprite::startMoving();
}

void TREnemy::endMoving(){
    TRSprite::endMoving();
}


#pragma mark - Animator Lockdown (PRIVATE)
void TREnemy::lock(int interval){
    anilockrem = interval;
    anilock = true;
    freeze();
}

void TREnemy::unlock(){
    defreeze();
    anilock = false;
}
