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
    flgPassBy = false;
    teleport_active = false;
    door_open = false;
}

bool TRMapTile::isPassBy(){
    return flgPassBy;
}

void TRMapTile::setPassBy(bool flg){
    flgPassBy = flg;
}

void TRMapTile::setType(TRMapTileType typ){
    type = typ;
    if (typ == TRMapTileTypeGround) {
        setPassBy(true);
        return;
    }
    if (typ == TRMapTileTypeWall) {
        setPassBy(false);
        return;
    }
    if(typ == TRMapTileTypeTeleport){
        setPassBy(true);
        return;
    }
}
TRMapTileType TRMapTile::getType(){
    return type;
}

void TRMapTile::openDoor(){
    linkTexture(dooropen_texture);
    setPassBy(true);
}
void TRMapTile::closeDoor(){
    linkTexture(doorclose_texture);
    setPassBy(false);
}
void TRMapTile::linkOpenTexutre(TRTexture* txt){
    dooropen_texture = txt;
}
void TRMapTile::linkCloseTexture(TRTexture* txt){
    doorclose_texture = txt;
}

void TRMapTile::setTeleportTarget(std::string target_map){
    teleport_target = target_map;
}
void TRMapTile::enableTeleporter(){
    teleport_active = true;
}
bool TRMapTile::isTeleportEnabled(){
    return teleport_active;
}
