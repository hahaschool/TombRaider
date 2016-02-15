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
#include "TRObject.hpp"

class TREnemy : public TRObject{
public:
    void beAttacked(int dmg);
private:
    
};

#endif /* TREnemy_hpp */
