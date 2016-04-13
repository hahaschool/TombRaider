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
#include <string>
#include <string.h>
#include <cstring>
#include "TRSprite.hpp"
#include "TRTimer.hpp"
#include "TRMapTile.hpp"
#include "TREnemy.hpp"
#include "TRSprite.hpp"
#include "TRHero.hpp"
#include "TRBgm.h"
#include "TRItem.hpp"
#include "TRTrap.hpp"
#include "TRInterface.h"

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
    //读入界面材质
    void loadTextureInterface();
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
    //读入陷阱默认值
    void loadDefaultTrap();
    //读入界面默认值
    void loadDefaultInterface();
    //读入子弹默认值
    void loadDefaultBullet();
    //载入地图
    void loadMapFromFile(std::string path);
    void loadLeadingMapFromFile(std::string path);

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
    //游戏胜利
    bool isGameWin();
    //游戏失败
    bool isGameFail();
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
    //创建陷阱
    void createTrap(std::string defaultKey,int x,int y,int h,int w);
    //创建子弹
    void createBullet(std::string defaultKey,int x,int y,TRBulletType typ,TRDirection dir);
    //创建血条
    void createHp(int x,int y,int h,int w);
    //创建界面
    void createInterface(std::string defaultKey,int x,int y,int h,int w,TRInterfaceType typ);
    //创建小地图
    //void createLeadingMapOut(int x,int y,int h,int w);
    //void createLeadingMapKey(int x,int y,int h,int w);
    void createLeadingMapOthers(int x,int y,int h,int w);

#pragma mark - 游戏进程控制
    //下一关
    void nextMap(int mapID);

#pragma mark - 文字

    void loadAndRenderFont(TTF_Font *font,std::string path,int fontSize,std::string text,SDL_Color textColor,int x,int y);

    //数字转化为字符串
    string changeIntToString(int n);
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
    bool flgGameWin;
    bool flgGameFail;

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

    std::vector<TRTexture *>interfaceTextureArray;

    //TRAnimator表
    std::vector<TRAnimator*> animatorArray;
    std::map<std::string,TRAnimator*> gAnimatorKeyMap;

    //TREnemy Hero Item Trap预置
    std::map<std::string,TREnemy *> defaultEnemyMap;
    std::map<std::string,TRHero *> defaultHeroMap;
    std::map<std::string,TRItem *> defaultItemMap;
    std::map<std::string,TRTrap *> defaultTrapMap;
    std::map<std::string,TRBullet *> defaultBulletMap;
    std::map<std::string,TRInterface *> defaultInterfaceMap;

    //全局Grider和寻路器
    TRGrider *gGrider;
    TRPathFinder *gPathFinder;
    TRBgm *gBgm;
    TRInterface *gInterface;

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
    //陷阱列表
    std::list<TRTrap*> gTrapList;

    //界面列表
    std::list<TRInterface *>gInterfaceList;

    //即将捡起物品标识
    bool willPickupItem;

    //英雄单位
    TRHero *hero;

    //全局摄像机
    SDL_Rect gCameraBox;
    //全局地图大小
    SDL_Rect gLevelBox;

    //小地图大小
    SDL_Rect gLeadingMapBox;
    //小地图地图块列表
    std::list<SDL_Rect*>gLeadingMapList;

    SDL_Rect hpRect;
    SDL_Rect hpOutlineRect;
    TTF_Font *font;
    SDL_Color textColor = {255,0,0};
    TRTexture *gTexture = new TRTexture;
    char t[256];
    int a =0,b = 0,c=780,d=0;
    string s;
    bool haveBeenSlow = false,keyBePicked = false;
    bool left = true;
    int keyX,keyY,outX,outY,heroX,heroY;
    SDL_Rect heroLeadingPisition;
    int mapID=2;
};

#endif /* TRGameController_hpp */
