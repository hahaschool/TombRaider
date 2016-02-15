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
#include "TREnemy.hpp"

class TRBullet : public TRSprite{
public:
    void attackHero(TRHero &hero);
    void attackEnemy(TRBullet &enemy);
    
private:
    int dmg;
    int vel;
};

#endif /* TRBullet_hpp */
