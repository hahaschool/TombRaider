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
#pragma mark - 对象生命周期
    //构造器和销毁器
    TRGameController();
    ~TRGameController();
    void free();
#pragma mark - 初始化／清除
    //全局初始化
    void initialize();
    //清空游戏舞台
    void clearStage();
    
#pragma mark - 文件读入
    //读入全部资源
    void loadResources();
    //读入材质文件 总方法
    void loadTexture();
    //读入地图块材质
    void loadTextureMaptile();
    //读入敌人材质
    void loadTextureEnemy();
    //读入英雄材质
    void loadTextureHero();
    //读入子弹材质
    void loadTextureBullet();
    //读入默认值 总方法
    void loadDefault();
    //读入动画器默认值
    void loadDefaultAnimator();
    //读入敌人默认值
    void loadDefaultEnemy();
    //读入英雄默认值
    void loadDefaultHero();
    //读入地图列表
    void loadDefaultMaplist();
    //读入道具默认值
    void loadDefaultItem();
    //载入地图
    void loadMapFromFile(std::string path);
    
#pragma mark - 对象参数设定
    //设定视野大笑
    void setCamera(int h,int w);
    //链接坐标转换器
    void linkGrider(TRGrider *grid);
    //链接寻路器
    void linkPathfinder(TRPathFinder *pf);
    //连接渲染器
    void linkRenderer(SDL_Renderer *renderer);
#pragma mark - 游戏生命周期
    //游戏开始
    void startGame();
    //判断游戏是否正在运行
    bool isGameRunning();
    //游戏暂停
    void pauseGame();
    void resumeGame();
    bool isGamePausing();
    //游戏结束
    void gameOver();
    //处理键盘事件
    void handleEvent(SDL_Event &e);
    //每帧的运算
    void runFrame();
    void render();
#pragma mark - 创建游戏部件
    //创建地图块
    void createMapTile(std::string textureKey,TRMapTileType type,int x,int y,int h,int w);
    //创建敌人
    void createEnemy(std::string defaultKey,int x,int y,int h,int w);
    //创建英雄
    void createHero(std::string defaultKey,int x,int y,int h,int w);
    //创建道具
    void createItem(std::string defaultKey,int x,int y,int h,int w);
    //创建血条
    void createHp(std::string defaultKey,int x,int y,int h,int w);
    
#pragma mark - 游戏进程控制
    //下一关
    void nextMap();
private:
    //调整镜头
    void centerCameraByObject(TRObject *obj);
    
    //基本碰撞检测
    bool checkCollision(SDL_Rect a,SDL_Rect b);
    
    
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
    
    //TREnemy Hero Item预置
    std::map<std::string,TREnemy *> defaultEnemyMap;
    std::map<std::string,TRHero *> defaultHeroMap;
    std::map<std::string,TRItem *> defaultItemMap;
    
    
    
    std::map<std::string,TRhp *>defaultHpMap;
    
    //全局Grider和寻路器
    TRGrider *gGrider;
    TRPathFinder *gPathFinder;
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
    
    
    //即将捡起物品标识
    bool willPickupItem;
    
    //英雄单位
    TRHero *hero;
    
    //全局摄像机
    SDL_Rect gCameraBox;
    //全局地图大小
    SDL_Rect gLevelBox;
    
};

#endif /* TRGameController_hpp */
