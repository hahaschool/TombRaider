//
//  TRMapTile.cpp
//  TombRaider
//
//  Created by 張正昊 on 13/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRMapTile.hpp"

bool TRMapTile::isPassBy(){
    return flgPassBy;
}

void TRMapTile::setPassBy(bool flg){
    flgPassBy = flg;
}