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
#include <iostream>
#include <fstream>
#include "TRSprite.hpp"
#include "TRTimer.hpp"
#include "TRMapTile.hpp"
#include "TREnemy.hpp"
#include "TRSprite.hpp"
#include "TRHero.hpp"
#include "TRBgm.h"
#include "TRhp.h"
#include "TRItem.hpp"

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
    
    //清除关卡
    void clearStage();
    
    //处理键盘事件
    void handleEvent(SDL_Event &e);
    
    //调整镜头
    void centerCameraByObject(TRObject *obj);
    
    //连接渲染器
    void linkRenderer(SDL_Renderer *renderer);
    
    //创建地图块
    void createMapTile(std::string textureKey,TRMapTileType type,int x,int y,int h,int w);
    
    //创建敌人
    void createEnemy(std::string defaultKey,int x,int y,int h,int w);
    
    //创建英雄
    void createHero(std::string defaultKey,int x,int y,int h,int w);
    
    //游戏开始
    void startGame();
    bool isGameRunning();
    
    //游戏暂停
    void pauseGame();
    void resumeGame();
    bool isGamePausing();
    
    //游戏结束
    void gameOver();
    
    //每帧的运算
    void runFrame();
    void render();
    
    //设定屏幕参数
    void setCamera(int h,int w);
    
    //Grider and PathFinder
    void linkGrider(TRGrider *grid);
    void linkPathfinder(TRPathFinder *pf);
    
    //基本碰撞检测
    bool checkCollision(SDL_Rect a,SDL_Rect b);
    
    //下一关
    void nextMap();
    
    
    void createHp(std::string defaultKey,int x,int y,int h,int w);
private:
    bool flgAttackPerformed;
    bool flgFired;
    TRBullet *lastFire;
    int keyCnt;
    
    bool flgGameStarted;
    bool flgGamePaused;
    
    //地图文件和物体分布文件路径
    std::string pathMapFramework;
    std::string pathDistribution;
    
    //地图路径表
    std::vector<std::string> mapPathArray;
    std::map<std::string,std::string> mapPathMap;
    
    //材质资源表
    std::vector<TRTexture *> mapTileTextureArray;
    std::vector<TRTexture *> enemyTextureArray;
    std::vector<TRTexture *> bulletTextureArray;
    std::vector<TRTexture *> heroTextureArray;
    std::map<std::string,TRTexture*> gTextureKeyMap;
    
    std::vector<TRTexture *>equipTextureArray;
    
    //TRAnimator表
    std::vector<TRAnimator*> animatorArray;
    std::map<std::string,TRAnimator*> gAnimatorKeyMap;
    
    //TREnemy Hero预置
    std::map<std::string,TREnemy *> defaultEnemyMap;
    std::map<std::string,TRHero *> defaultHeroMap;
    
    std::map<std::string,TRhp *>defaultHpMap;
    
    //全局Grider和寻路器
    TRGrider *gGrider;
    TRPathFinder *gPathFinder;
    TRGameController *gGameController;
    TRBgm *gBgm;
    TRhp *heroHp;
    
    //全局渲染器
    SDL_Renderer *gRenderer;
    
    //地图部件列表
    std::list<TRMapTile*> gMapTileList;
    
    //怪物列表
    std::list<TREnemy*> gEnemyList;
    
    //子弹列表
    std::list<TRBullet*> gBulletList;
    
    //道具列表
    std::list<TRItem*> gItemList;
    
    //英雄单位
    TRHero *hero;
    
    //全局摄像机
    SDL_Rect gCameraBox;
    //全局地图大小
    SDL_Rect gLevelBox;
    
    int mapIs[51][51];
    TRMapTile *gMapTile;
    bool mapTileBeCatched;
    int someThingJ;
    int someThingI;
};

#endif /* TRGameController_hpp */
