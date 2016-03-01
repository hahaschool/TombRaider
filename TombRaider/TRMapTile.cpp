//
//  TRMapTile.cpp
//  TombRaider
//
//  Created by 張正昊 on 13/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRMapTile.hpp"

TRMapTile::TRMapTile(){
    setCurClip({0,0,getWidth(),getHeight()});
}

bool TRMapTile::isPassBy(){
    return flgPassBy;
}

void TRMapTile::setPassBy(bool flg){
    flgPassBy = flg;
}