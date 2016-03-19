//
//  TRTrap.hpp
//  TombRaider
//
//  Created by 張正昊 on 19/3/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRTrap_hpp
#define TRTrap_hpp

#include <stdio.h>
#include "TRMapTile.hpp"
#include "TRhero.hpp"

enum TRTrapType{
    //陷阱伤害类型
    TRTrapSlow = 1,
    TRTrapBleed = 2,
    TRTrapNoGun = 4,
    TRTrapFreeze = 8,
    //离开陷阱区域是否依然有效果(Lasting:将给Hero施加一次较长的Debuff后休眠，Ephermal:将不断给Hero施加较短的Debuff，不休眠)
    //注意Freeze陷阱一定是Lasting的，而且休眠时间要足够长，保证Hero走出陷阱作用区
    TRTrapLasting = 16,
    TRTrapEphermal = 32,
};

class TRTrap : public TRMapTile{
public:
    //构造器
    TRTrap();
    //减速型陷阱设定
    void setSlowdownValue(int val);
    
    //掉血型陷阱设定
    void setBleedValue(int val);
    
    //设定施加的不良状态持续时间
    void setDebuffInterval(int interval);
    
    //设定类型
    void setType(int typ);
    
    //陷阱发动
    void activate();
    
    //设定陷阱休眠时间
    void setSleepTime(int cdt);
    
    //冷却时间自减
    void tickSleep();
    
    //渲染函数
    void render();
    
    void linkHero(TRHero *hro);
private:
    TRHero *hero;
    int type;
    int cd;
    int cd_rem;
    int slowval;
    int bleedval;
    int debuff_interval;
};

#endif /* TRTrap_hpp */
