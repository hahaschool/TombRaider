//
//  TRBullet.cpp
//  TombRaider
//
//  Created by 張正昊 on 15/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRBullet.hpp"

#pragma mark - 属性
int TRBullet::getSpeed(){
    return vel;
}

void TRBullet::setSpeed(int nvel){
    vel = nvel;
}

int TRBullet::getDamage(){
    return dmg;
}

void TRBullet::setDamage(int ndmg){
    dmg = ndmg;
}

TRBulletType TRBullet::getType(){
    return type;
}

void TRBullet::setType(TRBulletType ntype){
    type = ntype;
}


#pragma mark - 方向
void TRBullet::setDirection(TRDirection ndir){
    TRSprite::setDirection(ndir);
    if(ndir == TRDirectionUp){
        setVelY(-vel);
        setVelX(0);
    }else if(ndir == TRDirectionLeft){
        setVelX(-vel);
        setVelY(0);
    }else if(ndir == TRDirectionRight){
        setVelX(vel);
        setVelY(0);
    }else{
        setVelX(0);
        setVelY(vel);
    }
}

#pragma mark - 着弹
void TRBullet::attackEnemy(TREnemy *obj){
    obj->beAttacked(dmg);
    used = true;
}

void TRBullet::attackHero(TRHero *obj){
    obj->beAttacked(dmg);
    used = true;
}

bool TRBullet::isUsed(){
    return used;
}

#pragma mark - 渲染
void TRBullet::render(){
    TRSprite::render();
}