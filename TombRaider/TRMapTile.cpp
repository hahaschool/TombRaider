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
