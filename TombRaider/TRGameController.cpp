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

void TRGameController::gameOver(){
    flgGameStarted = false;
    flgGamePaused = false;
}

void TRGameController::handleEvent(SDL_Event &e){
    while (SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT){
            gameOver();
        }else if (e.type == SDL_KEYDOWN ) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    if(e.key.repeat == 0){
                        keyCnt++;
                    }
                    printf("keyup UP\n");
                    hero -> startMoveUp();
                    break;
                case SDLK_DOWN:
                    if(e.key.repeat == 0){
                        keyCnt++;
                    }
                    printf("keyup DOWN\n");
                    hero -> startMoveDown();
                    break;
                case SDLK_LEFT:
                    if(e.key.repeat == 0){
                        keyCnt++;
                    }
                    printf("keyup LEFT\n");
                    hero -> startMoveLeft();
                    break;
                case SDLK_RIGHT:
                    if(e.key.repeat == 0){
                        keyCnt++;
                    }
                    printf("keyup RIGHT\n");
                    hero -> startMoveRight();
                    break;
                case SDLK_z:
                    flgAttackPerformed = hero -> performAttack();
                case SDLK_x:
                    lastFire = hero -> fire();
                    flgFired = lastFire != NULL;
                default:
                    break;
            }
        }else if(e.type == SDL_KEYUP && e.key.repeat == 0){
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_DOWN:
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    if(e.key.repeat == 0){
                        keyCnt--;
                    }
                    if (keyCnt == 0) {
                        hero -> endMoving();
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void TRGameController::runFrame(){
    if (isGamePausing()) {
        //Do something about pause
        return;
    }
    if(!isGameRunning()){
        return;
    }
    
    //Calculate moving
    for(std::list<TREnemy*>::iterator it = gEnemyList.begin(); it != gEnemyList.end(); it++){
        (*it) -> move();
        for(std::list<TRMapTile*>::iterator itt = gMapTileList.begin();itt != gMapTileList.end();itt++){
            if(checkCollision((*it)->getBoxRect(), (*itt)->getBoxRect())){
                (*it) -> undo();
            }
        }
    }
    hero -> move();
    for(std::list<TRMapTile*>::iterator itt = gMapTileList.begin();itt != gMapTileList.end();itt++){
        if(checkCollision(hero->getBoxRect(), (*itt)->getBoxRect())){
            hero -> undo();
        }
    }
    
    //Refocus the camera
    centerCameraByObject(hero);
    
    //Calculate Bullets
    
    //Calculate Attacks
    if (flgAttackPerformed) {
        for(std::list<TREnemy*>::iterator it = gEnemyList.begin(); it != gEnemyList.end(); it++){
            if(checkCollision((*it)->getBoxRect(), hero->getBoxRect())){
                hero -> attack((*it));
            }
        }
        flgAttackPerformed = false;
    }
    
    //Delete dead Enemys
    for(std::list<TREnemy*>::iterator it = gEnemyList.begin(); it != gEnemyList.end(); it++){
        if(!(*it)->isAlive()){
            gEnemyList.erase(it);
            it--;
        }
    }
    
    //Calculate debuffs
    
    
    //Render all
    
    for(std::list<TRMapTile*>::iterator it = gMapTileList.begin();it != gMapTileList.end();it++){
        (*it) -> render();
    }
    for(std::list<TREnemy*>::iterator it = gEnemyList.begin(); it != gEnemyList.end(); it++){
        (*it) -> render();
    }
    for(std::list<TRBullet*>::iterator it = gBulletList.begin();it != gBulletList.end();it++){
        (*it) -> render();
    }
    hero -> render();
}


TRGameController::TRGameController(){
    gLevelBox = {0,0,1920,1080};
    keyCnt = 0;
}

TRGameController::~TRGameController(){
    free();
}

void TRGameController::free(){
    for(std::list<TRMapTile*>::iterator it = gMapTileList.begin();it != gMapTileList.end();it++){
        delete (*it);
    }
    for(std::list<TREnemy*>::iterator it = gEnemyList.begin(); it != gEnemyList.end(); it++){
        delete (*it);
    }
    for(std::list<TRBullet*>::iterator it = gBulletList.begin();it != gBulletList.end();it++){
        delete (*it);
    }
    for(int i = 0; i < mapTileTextureArray.size(); i++){
        delete mapTileTextureArray[i];
    }
    for(int i = 0; i < enemyTextureArray.size(); i++){
        delete enemyTextureArray[i];
    }
    for(int i = 0; i < bulletTextureArray.size(); i++){
        delete bulletTextureArray[i];
    }
    for(int i = 0; i < heroTextureArray.size(); i++){
        delete heroTextureArray[i];
    }
    for(int i = 0; i < animatorArray.size(); i++){
        delete animatorArray[i];
    }
    for(std::map<std::string,TREnemy *>::iterator it = defaultEnemyMap.begin(); it != defaultEnemyMap.end(); it++){
        delete (*it).second;
    }
    for(std::map<std::string,TRHero *>::iterator it = defaultHeroMap.begin(); it != defaultHeroMap.end();it++){
        delete (*it).second;
    }
}

void TRGameController::loadResources(){
    //init
    mapPathArray.clear();
    mapPathMap.clear();
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
    while (ifs.peek() == '/') {
        std::string filter;
        std::getline(ifs,filter);
    }
    int n;
    ifs >> n;
    mapTileTextureArray.resize(n+1);
    for(int i = 1; i <= n; i++){
        int id;
        std::string name,path;
        TRTexture *tex = new TRTexture;
        tex -> linkRenderer(gRenderer);
        ifs >> id >> name >> path;
        tex -> loadFromFile(path);
        mapTileTextureArray[id] = tex;
        gTextureKeyMap[name] = tex;
    }
    ifs.close();
    //载入怪物贴图
    ifs.open("Resources/Config/Texture_Enemy.cfg");
    while (ifs.peek() == '/') {
        std::string filter;
        std::getline(ifs,filter);
    }
    ifs >> n;
    enemyTextureArray.resize(n+1);
    for(int i = 1; i <= n; i++){
        int id;
        std::string name,path;
        TRTexture *tex = new TRTexture;
        tex -> linkRenderer(gRenderer);
        ifs >> id >> name >> path;
        tex -> loadFromFile(path);
        enemyTextureArray[id] = tex;
        gTextureKeyMap[name] = tex;
    }
    ifs.close();
    //载入英雄贴图
    ifs.open("Resources/Config/Texture_Hero.cfg");
    while (ifs.peek() == '/') {
        std::string filter;
        std::getline(ifs,filter);
    }
    ifs >> n;
    heroTextureArray.resize(n+1);
    for(int i = 1; i <= n; i++){
        int id;
        std::string name,path;
        TRTexture *tex = new TRTexture;
        tex -> linkRenderer(gRenderer);
        ifs >> id >> name >> path;
        tex -> loadFromFile(path);
        heroTextureArray[id] = tex;
        gTextureKeyMap[name] = tex;
    }
    ifs.close();
    //载入子弹贴图
    ifs.open("Resources/Config/Texture_Bullet.cfg");
    while (ifs.peek() == '/') {
        std::string filter;
        std::getline(ifs,filter);
    }
    ifs >> n;
    bulletTextureArray.resize(n+1);
    for(int i = 1; i <= n; i++){
        int id;
        std::string name,path;
        TRTexture *tex = new TRTexture;
        tex -> linkRenderer(gRenderer);
        ifs >> id >> name >> path;
        tex -> loadFromFile(path);
        bulletTextureArray[id] = tex;
        gTextureKeyMap[name] = tex;
    }
    ifs.close();
    //载入Animator
    ifs.open("Resources/Config/Animator.cfg");
    while (ifs.peek() == '/') {
        std::string filter;
        std::getline(ifs,filter);
    }
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
            ani -> appendClipRect({x,y,w,h});
        }
        ani -> setRateByFramePerClip(fpc);
        gAnimatorKeyMap[name] = ani;
        animatorArray[id] = ani;
    }
    ifs.close();
    //载入Enemy
    ifs.open("Resources/Config/Enemy.cfg");
    while (ifs.peek() == '/') {
        std::string filter;
        std::getline(ifs,filter);
    }
    ifs >> n;
    for(int i = 1; i<= n; i++){
        int id;
        std::string name,type,flg;
        TREnemy *enm = new TREnemy;
        enm -> linkCameraRect(&gCameraBox);
        enm -> linkLevelRect(&gLevelBox);
        enm -> linkGrider(gGrider);
        enm -> linkPathFinder(gPathFinder);
        ifs >> id >> name >> type;
        defaultEnemyMap[name] = enm;
        if (type == "random") {
            enm -> setType(TREnemyRandom);
        }else if(type == "smart"){
            enm -> setType(TREnemySmart);
        }
        int hp,dmg,arm,vel,cd;
        ifs >> hp >> dmg >> arm >> vel >> cd;
        enm -> setHP(hp);
        enm -> setDamage(dmg);
        enm -> setSpeed(vel);
        enm -> setArmour(arm);
        enm -> setAttackCD(cd);
        ifs >> name;
        enm -> linkTexture(gTextureKeyMap[name]);
        for(int j = 0; j < 4; j++){
            int x,y,h,w;
            ifs >> x >> y >> h >> w;
            enm -> setStaticClip({x,y,w,h}, (TRDirection)j);
        }
        for(int j = 0; j < 4; j++){
            int x,y,h,w;
            ifs >> x >> y >> h >> w;
            enm -> setDeathClip({x,y,w,h}, (TRDirection)j);
        }
        ifs >> flg;
        if(flg == "yes"){
            enm -> setWalkingAnimated(true);
            for(int j = 0; j < 4; j++){
                ifs >> name;
                enm -> setWalkingAnimator(gAnimatorKeyMap[name], (TRDirection)j);
            }
        }else{
            enm -> setWalkingAnimated(false);
        }
        ifs >> flg;
        if(flg == "yes"){
            enm -> setAttackingAnimated(true);
            for(int j = 0; j < 4; j++){
                ifs >> name;
                enm -> setAttackingAnimator(gAnimatorKeyMap[name], (TRDirection)j);
            }
        }else{
            enm -> setAttackingAnimated(false);
        }
    }
    ifs.close();
    //载入Hero
    ifs.open("Resources/Config/Hero.cfg");
    while (ifs.peek() == '/') {
        std::string filter;
        std::getline(ifs,filter);
    }
    ifs >> n;
    for (int i = 1; i <= n; i++) {
        int id;
        std::string name;
        TRHero *ho = new TRHero;
        ho -> linkCameraRect(&gCameraBox);
        ho -> linkLevelRect(&gLevelBox);
        ifs >> id >> name;
        defaultHeroMap[name] = ho;
        int hp,arm,dmg,vel,cd,bdmg,bvl;
        ifs >> hp >> arm >> dmg >> vel >> cd >> bdmg >> bvl;
        ho -> setHP(hp);
        ho -> setMaxHP(hp);
        ho -> setVelocity(vel);
        ho -> setDamage(dmg);
        ho -> setAttackCD(cd);
        ho -> setArmour(arm);
        ho -> setBulletDamage(bdmg);
        ho -> setBulletSpeed(bvl);
        ifs >> name;
        ho -> linkTexture(gTextureKeyMap[name]);
        for(int j = 0; j < 4; j++){
            int x,y,h,w;
            ifs >> x >> y >> h >> w;
            ho -> setStaticClip({x,y,w,h}, (TRDirection)j);
        }
        for(int j = 0; j < 4; j++){
            int x,y,h,w;
            ifs >> x >> y >> h >> w;
            ho -> setDeathClip({x,y,w,h}, (TRDirection)j);
        }
        std::string flg;
        ifs >> flg;
        if(flg == "yes"){
            ho -> setWalkingAnimated(true);
            for(int j = 0; j < 4; j++){
                ifs >> name;
                ho -> setWalkingAnimator(gAnimatorKeyMap[name], (TRDirection)j);
            }
        }else{
            ho -> setWalkingAnimated(false);
        }
        ifs >> flg;
        if(flg == "yes"){
            ho -> setAttackingAnimated(true);
            for(int j = 0; j < 4; j++){
                ifs >> name;
                ho -> setAttackingAnimator(gAnimatorKeyMap[name], (TRDirection)j);
            }
        }else{
            ho -> setAttackingAnimated(false);
        }
        ifs >> flg;
        if(flg == "yes"){
            ho -> setFiringAnimated(true);
            for(int j = 0; j < 4; j++){
                ifs >> name;
                ho -> setFiringAnimator(gAnimatorKeyMap[name], (TRDirection)j);
            }
        }else{
            ho -> setFiringAnimated(false);
        }
        ifs >> flg;
        if(flg == "yes"){
            ho -> setStandingAnimated(true);
            for(int j = 0; j < 4; j++){
                ifs >> name;
                ho -> setStandingAnimator(gAnimatorKeyMap[name], (TRDirection)j);
            }
        }else{
            ho -> setStandingAnimated(false);
        }
    }
    ifs.close();
    //载入地图列表
    ifs.open("Resources/Config/Map.cfg");
    while (ifs.peek() == '/') {
        std::string filter;
        std::getline(ifs,filter);
    }
    ifs >> n;
    mapPathArray.resize(n+1);
    for(int i = 1; i<= n; i++){
        std::string name,path;
        int id;
        ifs >> id >> name >> path;
        mapPathMap[name] = path;
        mapPathArray[id] = path;
    }
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

void TRGameController::createMapTile(std::string textureKey,TRMapTileType type,int x,int y,int h,int w){
    TRMapTile *tile = new TRMapTile;
    tile -> setX(x);
    tile -> setY(y);
    tile -> setWidth(w);
    tile -> setHeight(h);
    tile -> setCurClip({0,0,w,h});
    tile -> linkCameraRect(&gCameraBox);
    tile -> linkLevelRect(&gLevelBox);
    tile -> linkTexture(gTextureKeyMap[textureKey]);
    gMapTileList.insert(gMapTileList.end(), tile);
}

void TRGameController::createEnemy(std::string defaultKey,int x,int y,int h,int w){
    TREnemy *ce = new TREnemy;
    *ce = *defaultEnemyMap[defaultKey];
    ce -> setX(x);
    ce -> setY(y);
    ce -> setHeight(h);
    ce -> setWidth(w);
    ce -> linkHero(hero);
    ce -> startMoving();
    gEnemyList.insert(gEnemyList.end(), ce);
}

void TRGameController::createHero(std::string defaultKey,int x,int y,int h,int w){
    TRHero *hr = new TRHero;
    *hr = *defaultHeroMap[defaultKey];
    hr -> setX(x);
    hr -> setY(y);
    hr -> setHeight(h);
    hr -> setWidth(w);
    hero = hr;
}



void TRGameController::startGame(){
    flgGameStarted = true;
    flgGamePaused = false;
}

void TRGameController::pauseGame(){
    flgGamePaused = true;
}

void TRGameController::resumeGame(){
    flgGamePaused = false;
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

void TRGameController::setCamera(int h,int w){
    gCameraBox.h = h;
    gCameraBox.w = w;
}

void TRGameController::linkGrider(TRGrider *grid){
    gGrider = grid;
}

void TRGameController::linkPathfinder(TRPathFinder *pf){
    gPathFinder = pf;
}


