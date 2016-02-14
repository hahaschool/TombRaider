//
//  TRGrider.hpp
//  TombRaider
//
//  Created by 張正昊 on 14/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRGrider_hpp
#define TRGrider_hpp

#include <stdio.h>

class TRGrider{
public:
    int levelHeight,levelWidth;
    int gridHeight,gridWidth;
    int tileHeight,tileWidth;
    void convertLevelCenterToGrid(int lvlX,int lvlY,int &gridX,int &gridY);
    void convertLevelTopLeftToGrid(int lvlX,int lvlY,int &gridX,int &gridY);
    void convertGridToLevelTopLeft(int gridX,int gridY,int &lvlX,int &lvlY);
    void convertGridToLevelCenter(int gridX,int gridY,int &lvlX,int &lvlY);
    void convertTopLeftToCenter(int tlX,int tlY,int &cX,int cY);
    void convertCenterToTopLeft(int cX,int cY,int &tlX,int &tlY);
};

#endif /* TRGrider_hpp */
