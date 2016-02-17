//
//  TRGameController.cpp
//  TombRaider
//
//  Created by 張正昊 on 13/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRGameController.hpp"

/*
 全流程：
 设定好游戏数据
 载入资源
 载入连通性地图，设定好pathFinder和Grider
 载入详细地图，设定好mapTileList
 载入怪物分布，设定好enemyList
 设定好Hero
 开始主循环
 
 主循环流程：
 响应输入，给Hero单位发信
 所有单位move()
 碰检，undo()掉不合格move
 碰检，检查Hero不良状态
 碰检，计算在场子弹造成伤害
 清除被子弹杀伤的怪物
 碰检，计算近身攻击杀伤
 清除被近身攻击杀伤的怪物
 碰检，计算Hero被弹情况
 做出死亡判定
 还剩下的物体全员render()
 如果死了就进入GG模式
 */



TRGameController::TRGameController(){
    
}

TRGameController::~TRGameController(){
    free();
}

void TRGameController::free(){
    
}

void TRGameController::loadResources(){
    //init
    gTextureKeyMap.clear();
    gAnimatorKeyMap.clear();
    mapTileTextureArray.clear();
    enemyTextureArray.clear();
    bulletTextureArray.clear();
    heroTextureArray.clear();
    defaultEnemyMap.clear();
    defaultHeroMap.clear();
    //载入地图贴图
    std::ifstream ifs("Resources/Config/Texture_Maptile.cfg");
    int n;
    ifs >> n;
    mapTileTextureArray.resize(n+1);
    for(int i = 1; i <= n; i++){
        int id;
        std::string name,path;
        TRTexture *tex = new TRTexture;
        ifs >> id >> name >> path;
        tex -> loadFromFile(path);
        mapTileTextureArray[id] = tex;
        gTextureKeyMap[name] = tex;
    }
    //载入怪物贴图
    ifs.open("Resources/Config/Texture_Enemy.cfg");
    ifs >> n;
    enemyTextureArray.resize(n+1);
    for(int i = 1; i <= n; i++){
        int id;
        std::string name,path;
        TRTexture *tex = new TRTexture;
        ifs >> id >> name >> path;
        tex -> loadFromFile(path);
        enemyTextureArray[id] = tex;
        gTextureKeyMap[name] = tex;
    }
    //载入英雄贴图
    ifs.open("Resources/Config/Texture_Hero.cfg");
    ifs >> n;
    heroTextureArray.resize(n+1);
    for(int i = 1; i <= n; i++){
        int id;
        std::string name,path;
        TRTexture *tex = new TRTexture;
        ifs >> id >> name >> path;
        tex -> loadFromFile(path);
        heroTextureArray[id] = tex;
        gTextureKeyMap[name] = tex;
    }
    //载入子弹贴图
    ifs.open("Resources/Config/Texture_Bullet.cfg");
    ifs >> n;
    bulletTextureArray.resize(n+1);
    for(int i = 1; i <= n; i++){
        int id;
        std::string name,path;
        TRTexture *tex = new TRTexture;
        ifs >> id >> name >> path;
        tex -> loadFromFile(path);
        bulletTextureArray[id] = tex;
        gTextureKeyMap[name] = tex;
    }
    //载入Animator
    ifs.open("Resources/Config/Animator.cfg");
    ifs >> n;
    animatorArray.resize(n+1);
    for(int i = 1; i <= n; i++){
        int id,fcnt,fpc;
        std::string name;
        ifs >> id >> name >> fpc >> fcnt;
        TRAnimator *ani = new TRAnimator;
        ani -> setLoop(true);
        for(int j = 1; j <= fcnt;j++){
            int x,y,h,w;
            ifs >> x >> y >> h >> w;
            ani -> appendClipRect({x,y,h,w});
        }
        ani -> setRateByFramePerClip(fpc);
        gAnimatorKeyMap[name] = ani;
        animatorArray[id] = ani;
    }
    
}

void TRGameController::handleEvent(SDL_Event &e){
    
}

void TRGameController::centerCameraByObject(TRObject *obj){
    gCameraBox.x = (obj->getX() + obj->getWidth()) - gCameraBox.w/2;
    gCameraBox.y = (obj->getY() + obj->getHeight()) - gCameraBox.h/2;
    if(gCameraBox.x < 0){
        gCameraBox.x = 0;
    }
    if(gCameraBox.y < 0){
        gCameraBox.y = 0;
    }
    if (gCameraBox.x > gLevelBox.w - gCameraBox.w) {
        gCameraBox.x = gLevelBox.w - gCameraBox.w;
    }
    if(gCameraBox.y > gLevelBox.h - gCameraBox.h){
        gCameraBox.y = gLevelBox.h - gCameraBox.h;
    }
}

void TRGameController::linkRenderer(SDL_Renderer *renderer){
    gRenderer = renderer;
}

void TRGameController::createMapTile(std::string textureKey,TRMapTileType type,int x,int y){
    
}


void TRGameController::startGame(){
    
}

void TRGameController::pauseGame(){
    
}

void TRGameController::resumeGame(){
    
}

bool TRGameController::isGamePausing(){
    return flgGamePaused;
}

bool TRGameController::isGameRunning(){
    if(flgGameStarted && !flgGamePaused){
        return true;
    }
    return false;
}

bool TRGameController::checkCollision(SDL_Rect a, SDL_Rect b){
        //The sides of the rectangles
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;
        
        //Calculate the sides of rect A
        leftA = a.x;
        rightA = a.x + a.w;
        topA = a.y;
        bottomA = a.y + a.h;
        
        //Calculate the sides of rect B
        leftB = b.x;
        rightB = b.x + b.w;
        topB = b.y;
        bottomB = b.y + b.h;
        
        //If any of the sides from A are outside of B
        if( bottomA <= topB ){
            return false;
        }
        if( topA >= bottomB ){
            return false;
        }
        if( rightA <= leftB ){
            return false;
        }
        if( leftA >= rightB ){
            return false;
        }
        
        //If none of the sides from A are outside B
        return true;
}




