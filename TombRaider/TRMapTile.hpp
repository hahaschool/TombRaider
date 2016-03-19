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
    void setType(TRMapTileType typ);
    
    //门相关
    void openDoor();
    void closeDoor();
    void linkOpenTexutre(TRTexture *txt);
    void linkCloseTexture(TRTexture *txt);
    
    //传送装置相关
    void setTeleportTarget(std::string target_map);
    void enableTeleporter();
    bool isTeleportEnabled();
    
private:
    //地图块是否可穿越
    bool flgPassBy;
    TRMapTileType type;
    
    //传送相关
    std::string teleport_target;
    bool teleport_active;
    
    //门相关
    bool door_open;
    TRTexture *dooropen_texture;
    TRTexture *doorclose_texture;
    
    
};

#endif /* TRMapTile_hpp */
