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
#include <algorithm>
#include <list>
#include <vector>
#include <map>
#include "TRSprite.hpp"
#include "TRTimer.hpp"
#include "TRMapTile.hpp"
#include "TREnemy.hpp"
#include "TRSprite.hpp"
#include "TRHero.hpp"
#include "TRKeyboardControl.h"

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
    void handleEvent(SDL_Event &e);
    
    //调整镜头
    void centerCameraByObject(TRObject *obj);
    
    //连接渲染器
    void linkRenderer(SDL_Renderer *renderer);
    
    //创建地图块
    void createMapTile(std::string textureKey,TRMapTileType type,int x,int y);
    
    //创建敌人
    void createEnemy();
    
    //游戏开始
    void startGame();
    bool isGameRunning();
    
    //游戏暂停
    void pauseGame();
    void resumeGame();
    bool isGamePausing();
    
    //基本碰撞检测
    bool checkCollision(SDL_Rect a,SDL_Rect b);
    
    //路径设定
    
    
private:
    bool flgGameStarted;
    bool flgGamePaused;
    
    //地图文件和物体分布文件路径
    std::string pathMapFramework;
    std::string pathDistribution;
    
    //材质资源表
    std::map<std::string,TRTexture*> gTextureMap;
    
    //TRAnimator表
    std::map<std::string,TRAnimator*> gAnimatorMap;
    
    //全局渲染器
    SDL_Renderer *gRenderer;
    
    //地图部件列表
    std::list<TRMapTile*> gMapTileList;
    
    //怪物列表
    std::list<TREnemy*> gEnemyList;
    
    //英雄单位
    TRHero *hero;
    
    //全局摄像机
    SDL_Rect gCameraBox;
    //全局地图大小
    SDL_Rect gLevelBox;
	
	//键盘处理类对象
	TRKeyboardControl *keyBoard;
	//英雄图像
	SDL_Surface heroStaticImage;
};

#endif /* TRGameController_hpp */
