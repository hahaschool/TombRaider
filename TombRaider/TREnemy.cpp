//
//  TREnemy.cpp
//  TombRaider
//
//  Created by 張正昊 on 13/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TREnemy.hpp"

TREnemy::TREnemy(){
    flgfire = false;
    anilock = false;
    anilockrem = 0;
    alive = true;
    chasing = false;
    turretMode = false;
    flgFollowMode = false;
    randrem = 0;
}

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

void TREnemy::setMaxHP(int mhp){
    maxHP = mhp;
}

int TREnemy::getMaxHP(){
    return maxHP;
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
        prv_hero_x = hero_gridX,prv_hero_y = hero_gridY;
        pathFinder->setStartingPoint(gridX, gridY);
        pathFinder->setTargetPoint(hero_gridX, hero_gridY);
        pathFinder->findPath();
        clearRoute();
        int tx,ty,ax,ay;
        while(pathFinder->extractPath(tx, ty)){
            grider->convertGridToLevelTopLeft(tx, ty, ax, ay);
            path.push(std::make_pair(ax,ay));
        }
        if (path.size()) {
            path.pop();
        }
    }
}

#pragma mark - 移动

void TREnemy::move(){
    if(anilock){
        anilockrem--;
        if(anilockrem <= 0){
            unlock();
            endAttacking();
        }
    }
    atk_cd_rem--;
    if (isMoving()) {
        if(type == TREnemyRandom){
            moveRandom();
        }else if(type == TREnemySmart){
            if(std::abs(hero->getX()-getX()) + std::abs(hero->getY()-getY()) > 100+rand()%250){
                clearRoute();
                moveRandom();
            }else{
                setVelXY(0);
                moveAlongPath();
            }
        }
        if(turretMode){
            if (--bul_cd_rem < 0) {
                bul_cd_rem = bul_cd;
                flgfire = true;
            }
        }
    }
}

void TREnemy::moveAlongPath(){
    planRoute(false);
    if(path.empty()){
        return;
    }
    int topX = path.front().first;
    int topY = path.front().second;
    int curX = getX();
    int curY = getY();
    if(!undoed && curX != topX){
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
        setX(curX);
        return;
    }
    if(curY != topY){
        undoed = false;
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
        setY(curY);
        return;
    }
    if(curX == topX && curY == topY){
        path.pop();
    }
    return;
}

void TREnemy::moveRandom(){
    if(randrem >= 30){
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
        randrem = 0;
        return;
    }
    randrem++;
    TRSprite::move();
}

void TREnemy::startMoving(){
    linkWalkingAnimator();
    TRSprite::startMoving();
}

void TREnemy::endMoving(){
    TRSprite::endMoving();
}

#pragma mark - 炮台设定
#pragma mark 设定炮台模式
void TREnemy::setTurretMode(bool flg){
    turretMode = flg;
}
#pragma mark 检测是否发出炮弹
bool TREnemy::willFire(){
    return flgfire;
}

#pragma mark 炮弹已经射出消息
void TREnemy::doneFire(){
    flgfire = false;
}

#pragma mark 设定成跟随当前方向发射
void TREnemy::setFollowMode(bool flg){
    flgFollowMode = flg;
}

#pragma mark 检测是否跟随当前方向发射
bool TREnemy::isFollowMode(){
    return flgFollowMode;
}

#pragma mark 开关炮弹的发射方向
void TREnemy::setFireDirection(TRDirection dir, bool flg){
    canfire[dir] = flg;
}

#pragma mark 设置子弹Key
void TREnemy::setBulletKey(std::string key){
    bulKey = key;
}

#pragma mark 获得子弹Key
std::string TREnemy::getBulletKey(){
    return bulKey;
}

#pragma mark 是否能在某个方向发出炮弹
bool TREnemy::canFireAt(TRDirection dir){
    return canfire[dir];
}

#pragma mark 设定炮弹发出间隔
void TREnemy::setFireCooldown(int intr){
    bul_cd = bul_cd_rem = intr;
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
