//
//  TRMapTile.hpp
//  TombRaider
//
//  Created by 張正昊 on 13/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRMapTile_hpp
#define TRMapTile_hpp

#include <stdio.h>
#include "TRObject.hpp"

enum TRMapTileType{
    TRMapTileTypeGround = 0,
    TRMapTileTypeWall = 1,
    TRMapTileTypeDoor = 2,
    TRMapTileTypeTeleport = 3
};

class TRMapTile : public TRObject{
public:
    TRMapTile();
    bool isPassBy();
    void setPassBy(bool flg);
private:
    //地图块是否可穿越
    bool flgPassBy;
};

#endif /* TRMapTile_hpp */
