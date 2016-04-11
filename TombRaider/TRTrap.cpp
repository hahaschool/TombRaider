//
//  TRTrap.cpp
//  TombRaider
//
//  Created by 張正昊 on 19/3/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRTrap.hpp"

#pragma mark - 构造器
TRTrap::TRTrap(){
    cd = 0;
    cd_rem = 0;
    slowval = 0;
    bleedval = 0;
    debuff_interval = 2;
}

#pragma mark - 减速陷阱
#pragma mark 设定减速值
void TRTrap::setSlowdownValue(int val){
    slowval = val;
}

#pragma mark - 掉血陷阱
#pragma mark 设定掉血速度
void TRTrap::setBleedValue(int val){
    bleedval = val;
}

#pragma mark - 通用设定
#pragma mark 设定陷阱类型
void TRTrap::setType(int typ){
    type = typ;
    if (typ & TRTrapEphermal) {
        cd = cd_rem = 0;
        debuff_interval = 2;
    }
}
#pragma mark - 返回陷阱类型
int TRTrap::getType()
{
    return type;
}
#pragma mark 设定不良状态施加时间
void TRTrap::setDebuffInterval(int interval){
    debuff_interval = interval;
}
#pragma mark 设定休眠时间
void TRTrap::setSleepTime(int cdt){
    cd = cdt;
}
#pragma mark 链接英雄
void TRTrap::linkHero(TRHero* hro){
    hero = hro;
}

#pragma mark - 生命周期
#pragma mark 冷却时间自减
void TRTrap::tickSleep(){
    if (cd_rem) {
        cd_rem--;
    }
}
#pragma mark 陷阱发动
void TRTrap::activate(){
    if (cd_rem) {
        return;
    }
    cd_rem = cd;
    if (type & TRTrapSlow) {
        hero -> debuff_Slow(debuff_interval, slowval);
    }else if(type & TRTrapBleed){
        hero -> debuff_Bleed(debuff_interval, bleedval);
    }else if(type & TRTrapNoGun){
        hero -> debuff_Nogun(debuff_interval);
    }else if(type & TRTrapFreeze){
        hero -> debuff_Freeze(debuff_interval);
    }
}
#pragma mark 渲染
void TRTrap::render(){
    tickSleep();
    TRMapTile::render();
}

