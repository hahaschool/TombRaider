//
//  TRGrider.cpp
//  TombRaider
//
//  Created by 張正昊 on 14/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRGrider.hpp"

void TRGrider::convertLevelCenterToGrid(int lvlX,int lvlY,int &gridX,int &gridY){
    gridX = lvlX / tileWidth;
    gridY = lvlY / tileHeight;
}

void TRGrider::convertLevelTopLeftToGrid(int lvlX,int lvlY,int &gridX,int &gridY){
    convertTopLeftToCenter(lvlX, lvlY, lvlX, lvlY);
    convertLevelCenterToGrid(lvlX, lvlY, gridX, gridY);
    
}

void TRGrider::convertGridToLevelTopLeft(int gridX,int gridY,int &lvlX,int &lvlY){
    lvlX = gridX * tileWidth;
    lvlY = gridY * tileHeight;
}

void TRGrider::convertGridToLevelCenter(int gridX,int gridY,int &lvlX,int &lvlY){
    convertGridToLevelTopLeft(gridX, gridY, lvlX, lvlY);
    convertTopLeftToCenter(lvlX, lvlY, lvlX, lvlY);
}

void TRGrider::convertTopLeftToCenter(int tlX,int tlY,int &cX,int cY){
    cX = tlX + tileWidth/2;
    cY = tlY + tileHeight/2;
}

void TRGrider::convertCenterToTopLeft(int cX,int cY,int &tlX,int &tlY){
    tlX = cX - tileWidth/2;
    tlY = cY - tileHeight/2;
}