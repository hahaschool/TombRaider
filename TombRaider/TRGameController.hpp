//
//  TRGameController.hpp
//  TombRaider
//
//  Created by 張正昊 on 13/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRGameController_hpp
#define TRGameController_hpp

#include <stdio.h>
#include "TRSprite.hpp"
#include "TRTimer.hpp"
#include "TRMapTile.hpp"
#include "TREnemy.hpp"
#include "TRSprite.hpp"
#include "TRHero.hpp"

class TRGameController{
public:
    //构造器和销毁器
    TRGameController();
    ~TRGameController();
    void free();
    
    //载入资源
    void loadResources();
    
    //载入地图
    void loadMapFromFile(std::string path);
    
    //处理键盘事件
    void handleKeyboardEvent(SDL_KeyboardEvent &e);
    
    //调整镜头
    void centerCameraByObject(TRObject *obj);
    
private:
    bool gameStarted;
    
    //全局渲染器
    SDL_Renderer *gRenderer;
    
    //地图部件列表
    
    //怪物列表
    
    //英雄单位
    TRHero hero;
    
    //全局摄像机
    SDL_Rect gCameraBox;
    //全局地图大小
    SDL_Rect gLevelBox;
};

#endif /* TRGameController_hpp */
