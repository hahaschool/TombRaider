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


#pragma mark - 初始化
void TRGameController::initialize(){
    //内部变量在这里都会被重置
    mapPathArray.clear();
    mapPathMap.clear();
    gTextureKeyMap.clear();
    gAnimatorKeyMap.clear();
    mapTileTextureArray.clear();
    enemyTextureArray.clear();
    bulletTextureArray.clear();
    heroTextureArray.clear();
    interfaceTextureArray.clear();
    defaultEnemyMap.clear();
    defaultHeroMap.clear();
    defaultItemMap.clear();
    defaultTrapMap.clear();
    defaultInterfaceMap.clear();
}

void TRGameController::clearStage(){
    //仅清理和游戏活动有关的项目
    for(std::list<TREnemy*>::iterator it = gEnemyList.begin(); it != gEnemyList.end(); it++){
        delete *it;
    }
    for(std::list<TRBullet*>::iterator it = gBulletList.begin(); it != gBulletList.end(); it++){
        delete *it;
    }
    for(std::list<TRItem*>::iterator it = gItemList.begin(); it != gItemList.end(); it++){
        delete *it;
    }
    for(std::list<TRTrap*>::iterator it = gTrapList.begin(); it != gTrapList.end(); it++){
        delete *it;
    }
    for(std::list<TRMapTile*>::iterator it = gMapTileList.begin(); it != gMapTileList.end(); it++){
        delete *it;
    }
    for (std::list<TRInterface*>::iterator it = gInterfaceList.begin(); it != gInterfaceList.end(); it++) {
        delete *it;
    }
    gMapTileList.clear();
    gEnemyList.clear();
    gBulletList.clear();
    gItemList.clear();
    gTrapList.clear();
    gInterfaceList.clear();
}

#pragma mark - 文件读入
#pragma mark 读入及解析地图文件
void TRGameController::loadLeadingMapFromFile(std::string path){
    std::ifstream ifs;
    ifs.open(path);
    int n,m;
    ifs>>n>>m;
    gLeadingMapBox.h=n*3;
    gLeadingMapBox.w=m*3;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char a;
            ifs>>a;
            if(a=='o'){
                //createLeadingMapOut(j*2,i*2,2,2);
                outX = j;
                outY = i;
            }else if(a=='k'){
                //createLeadingMapKey(j*2,i*2,2,2);
                keyX = j;
                keyY = i;
            }else if(a=='0'||a=='i'||a=='b'){
                createLeadingMapOthers(j*3,i*3,3,3);
            }
        }
    }
    ifs.close();
}

void TRGameController::loadMapFromFile(std::string path){
    std::ifstream ifs;
    ifs.open(path);
    int n,m;
    ifs >> n >> m;
    gLevelBox.h = n*50;
    gLevelBox.w = m*50;
    gGrider->levelHeight = gLevelBox.h;
    gGrider->levelWidth = gLevelBox.w;
    gGrider->gridHeight = n;
    gGrider->gridWidth = m;
    gPathFinder->init(n, m, 10);
    createMapTile("background7",TRMapTileTypeGround,0,0,1500,1500);
    createInterface("interface/treasure/gold",15,720,30,30,TRInterfaceTypeTreasure);
    createInterface("interface/bullet/superpack",165,720,30,30,TRInterfaceTypeBullet);
    if(hero == NULL) createHero("hahaschool", 50, 50, 48, 32);
    else hero->setX(50),hero->setY(50);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char a;
            ifs >> a;
            switch(a){
                case '0':
                    gPathFinder->setMatrix(j, i, TRPathFinderMatrixObstacle);
                    createMapTile("wall/iron", TRMapTileTypeWall, j*50, i*50, 50, 50);
                    break;
                case 'o':
                    gPathFinder->setMatrix(j,i,TRPathFinderMatrixRoad);
                    createMapTile("wall/out",TRMapTileTypeTeleport,j*50,i*50,50,50);
                    break;
                case 'w':
                    gPathFinder->setMatrix(j,i,TRPathFinderMatrixRoad);
                    createTrap("trap/slow/water", j*50, i*50, 50, 50);
                    break;
                case 't':
                    createMapTile("map/tree",TRMapTileTypeGround,j*50,i*50,50,50);
                    gPathFinder->setMatrix(j,i,TRPathFinderMatrixRoad);
                    break;
                case 'i':
                    createMapTile("inside/iron",TRMapTileTypeWall, j*50, i*50, 50, 50);
                    break;
                case '1':
                    gPathFinder->setMatrix(j, i, TRPathFinderMatrixRoad);
                    break;
                case 'm':
                    createMapTile("mummy",TRMapTileTypeGround, j*50, i*50, 50, 50);
                    break;
                case 'k':
                    createItem("item/key/gold", j*50, i*50, 40, 40);
                    break;
                case '$':
                    createItem("item/treasure/gold", j*50, i*50, 40, 40);
                    break;
                case 'r':
                    createItem("item/bullet/superpack", j*50, i*50, 50, 50);
                    break;
                case '+':
                    createItem("item/heal/medicpack", j*50, i*50, 50, 50);
                    break;
                case 'l':
                    createItem("item/heal/herb", j*50, i*50, 50, 50);
                    break;
                case 'b':
                    gPathFinder->setMatrix(j, i, TRPathFinderMatrixObstacle);
                    createMapTile("map/brick",TRMapTileTypeWall, j*50, i*50, 50, 50);
                    break;
                case 'g':
                    createEnemy("guard",j*50,i*50,50,37.5);
                    break;
                case 'd':
                    createTrap("trap/bleed/dilei",j*50,i*50,50,50);
                    break;
                case 's':
                    createItem("item/sandanqiang/gun2",j*50,i*50,50,100);
                    break;
                case 'p':
                    //createEnemy("pharaoh",j*50,i*50,50,50);
                    break;
            }
        }
    }
}

#pragma mark 读入全部资源文件
void TRGameController::loadResources(){
    loadTexture();
    loadDefault();
}

#pragma mark 读入材质文件 总方法
void TRGameController::loadTexture(){
    loadTextureMaptile();
    loadTextureEnemy();
    loadTextureHero();
    loadTextureBullet();
    loadTextureInterface();
}

#pragma mark 读入地图块材质
void TRGameController::loadTextureMaptile(){
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
}

#pragma mark 读入敌人材质
void TRGameController::loadTextureEnemy(){
    std::ifstream ifs("Resources/Config/Texture_Enemy.cfg");
    int n;
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
}

#pragma mark 读入英雄材质
void TRGameController::loadTextureHero(){
    std::ifstream ifs("Resources/Config/Texture_Hero.cfg");
    int n;
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
}

#pragma mark 读入子弹材质
void TRGameController::loadTextureBullet(){
    std::ifstream ifs("Resources/Config/Texture_Bullet.cfg");
    int n;
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
}

void TRGameController::loadTextureInterface(){
    std::ifstream ifs("Resources/Config/Texture_Interface.cfg");
    int n;
    while(ifs.peek()=='/'){
        std::string filter;
        std::getline(ifs,filter);
    }
    ifs >> n;
    interfaceTextureArray.resize(n+1);
    for(int i = 1; i <= n; i++){
        int id;
        std::string name,path;
        TRTexture *tex = new TRTexture;
        tex->linkRenderer(gRenderer);
        ifs >> id >> name >> path;
        tex->loadFromFile(path);
        interfaceTextureArray[id] = tex;
        gTextureKeyMap[name] = tex;
    }
    ifs.close();
}
#pragma mark 读入默认值 总方法
void TRGameController::loadDefault(){
    loadDefaultAnimator();
    loadDefaultEnemy();
    loadDefaultHero();
    loadDefaultMaplist();
    loadDefaultItem();
    loadDefaultTrap();
    loadDefaultBullet();
    loadDefaultInterface();
}

#pragma mark 读入动画器默认值
void TRGameController::loadDefaultAnimator(){
    std::ifstream ifs("Resources/Config/Animator.cfg");
    int n;
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
}

#pragma mark 读入敌人默认值
void TRGameController::loadDefaultEnemy(){
    std::ifstream ifs("Resources/Config/Enemy.cfg");
    int n;
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
        }else if(type == "turret"){
            enm -> setType(TREnemyTurret);
            enm -> setTurretMode(true);
        }
        int hp,dmg,arm,vel,cd;
        ifs >> hp >> dmg >> arm >> vel >> cd;
        enm -> setHP(hp);
        enm -> setMaxHP(hp);
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
        ifs >> flg;
        if (flg == "yes") {
            enm -> setTurretMode(true);
            //炮台追加设定
            std::string bname;
            int bcd;
            ifs >> flg;
            if(flg == "manual"){
                for(int j = 0; j < 4; j++){
                    ifs >> flg;
                    if(flg == "yes"){
                        enm -> setFireDirection((TRDirection)j, true);
                    }else{
                        enm -> setFireDirection((TRDirection)j, false);
                    }
                }
            }else if(flg == "follow"){
                enm -> setFollowMode(true);
            }

            ifs >> bname >> bcd;
            enm -> setBulletKey(bname);
            enm -> setFireCooldown(bcd);
        }
    }
    ifs.close();
}

#pragma mark 读入英雄默认值
void TRGameController::loadDefaultHero(){
    std::ifstream ifs("Resources/Config/Hero.cfg");
    int n;
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
        int hp,arm,dmg,vel,cd,treasure,bulletNum,zNum;
        std::string bname,flg;
        ifs >> hp >> arm >> dmg >> vel >> cd >> treasure >> bulletNum >> zNum >> flg >> bname;
        ho -> setHP(hp);
        ho -> setMaxHP(hp);
        ho -> setVelocity(vel);
        ho -> setDamage(dmg);
        ho -> setAttackCD(cd);
        ho -> setArmour(arm);
        ho -> setTreasure(treasure);
        ho -> setBulletNum(bulletNum);
        ho -> setBulletKey(bname);
        ho -> setZnum(zNum);
        ho -> setAttackRangeFactor(0.8);
        ho -> setColliderFactor(0.8);
        if(flg == "yes")
        {
            ho->setGotTheKey(true);
        }else
        {
            ho->setGotTheKey(false);
        }
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
}

#pragma mark 读入地图列表
void TRGameController::loadDefaultMaplist(){
    std::ifstream ifs("Resources/Config/Map.cfg");
    int n;
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
    ifs.close();
}

#pragma mark 读入道具默认值
void TRGameController::loadDefaultItem(){
    std::ifstream ifs("Resources/Config/Item.cfg");
    int n;
    while (ifs.peek() == '/') {
        std::string filter;
        std::getline(ifs, filter);
    }
    ifs >> n;
    for(int i = 1; i <= n; i++){
        int id,ww,hh;
        std::string name,tname,type;
        ifs >> id >> name >> tname >> ww >> hh >> type;
        TRItem *ndt = new TRItem;
        ndt -> linkTexture(gTextureKeyMap[tname]);
        ndt -> linkLevelRect(&gLevelBox);
        ndt -> linkCameraRect(&gCameraBox);
        ndt -> setWidth(ww);
        ndt -> setHeight(hh);
        ndt -> marker_texture = gTextureKeyMap["action/catch"];
        ndt -> setCurClip({0,0,ww,hh});
        ndt -> setType(TRMapTileTypeGround);
        ndt -> linkCameraRect(&gCameraBox);
        ndt -> linkLevelRect(&gLevelBox);
        if(type == "HEAL"){
            ndt -> setItemType(TRItemHeal);
            int delta;
            ifs >> delta;
            ndt -> setHealingValue(delta);
        }else if(type == "BULLET"){
            ndt -> setItemType(TRItemBullet);
            int delta;
            ifs >> delta;
            ndt -> setBulletValue(delta);
        }else if(type == "KEY"){
            ndt -> setItemType(TRItemKey);
        }else if(type == "TREASURE"){
            ndt -> setItemType(TRItemTreasure);
        }else if(type == "GUN"){
            ndt->setItemType(TRItemGun2);
            int sandanNum;
            ifs >> sandanNum;
            ndt->setSandanValue(sandanNum);
        }
        defaultItemMap[name] = ndt;
    }
    ifs.close();
}

#pragma mark 读入界面默认值
void TRGameController::loadDefaultInterface(){
    std::ifstream ifs("Resources/Config/Interface.cfg");
    int n;
    while(ifs.peek()=='/'){
        std::string filter;
        std::getline(ifs,filter);
    }
    ifs >> n;
    for(int i = 1; i <= n; i++){
        int id,ww,hh;
        std::string name,tname,type;
        ifs >> id >> name >> tname >> ww >> hh >> type;
        TRInterface *itf = new TRInterface;
        itf->linkTexture(gTextureKeyMap[tname]);
        itf->setWidth(ww);
        itf->setHeight(hh);
        itf->setCurClip({0,0,ww,hh});
        if(type == "BULLET"){
            itf->setInterfaceType(TRInterfaceTypeBullet);
        }else if(type=="TREASURE"){
            itf->setInterfaceType(TRInterfaceTypeTreasure);
        }else if(type=="KEY"){
            itf->setInterfaceType(TRInterfaceTypeKey);
        }else if(type == "LOWSPEED"){
            itf->setInterfaceType(TRInterfaceTypeLowspeed);
        }
        defaultInterfaceMap[name] = itf;
    }
    ifs.close();
}

#pragma mark 读入陷阱默认值
void TRGameController::loadDefaultTrap(){
    std::ifstream ifs("Resources/Config/Trap.cfg");
    int n;
    while (ifs.peek() == '/') {
        std::string filter;
        std::getline(ifs, filter);
    }
    ifs >> n;
    for(int i = 1;i <= n; i++){
        int id,ww,hh,arg1;
        std::string name,tname,type1,type2;
        ifs >> id >> name >> tname >> ww >> hh >> type1 >> arg1 >> type2;
        TRTrap *ntr = new TRTrap;
        ntr -> setPassBy(true);
        ntr -> linkCameraRect(&gCameraBox);
        ntr -> linkLevelRect(&gLevelBox);
        ntr -> linkTexture(gTextureKeyMap[tname]);
        ntr -> setWidth(ww);
        ntr -> setHeight(hh);
        ntr -> setColliderFactor(0.8);
        ntr -> setCurClip({0,0,ww,hh});
        if(type1 == "SLOW"){
            ntr -> setSlowdownValue(arg1);
            if (type2 == "EPHERMAL") {
                ntr -> setType(TRTrapSlow | TRTrapEphermal);
            }else{
                ntr -> setType(TRTrapSlow | TRTrapLasting);
                int sleeptime,arg2;
                ifs >> sleeptime >> arg2;
                ntr -> setSleepTime(sleeptime);
                ntr -> setDebuffInterval(arg2);
            }
        }else if(type1 == "BLEED"){
            ntr -> setBleedValue(arg1);
            if (type2 == "EPHERMAL") {
                ntr -> setType(TRTrapBleed | TRTrapEphermal);
            }else{
                ntr -> setType(TRTrapBleed | TRTrapLasting);
                int sleeptime,arg2;
                ifs >> sleeptime >> arg2;
                ntr -> setSleepTime(sleeptime);
                ntr -> setDebuffInterval(arg2);
            }
        }else if(type1 == "FREEZE"){
            if (type2 == "LAST") {
                ntr -> setType(TRTrapFreeze | TRTrapLasting);
                int arg2;
                ifs >> arg2;
                ntr -> setSleepTime(arg1);
                ntr -> setDebuffInterval(arg2);
                ntr -> setColliderFactor(0.1);
            }
        }else if(type1 == "NOGUN"){
            if (type2 == "EPHERMAL") {
                ntr -> setType(TRTrapNoGun | TRTrapEphermal);
            }else{
                ntr -> setType(TRTrapNoGun | TRTrapLasting);
                int sleeptime,arg2;
                ifs >> sleeptime >> arg2;
                ntr -> setSleepTime(sleeptime);
                ntr -> setDebuffInterval(arg2);
            }
        }
        defaultTrapMap[name] = ntr;
    }
    ifs.close();
}

#pragma mark 读入子弹默认值
void TRGameController::loadDefaultBullet(){
    std::ifstream ifs("Resources/Config/Bullet.cfg");
    int n;
    while (ifs.peek() == '/') {
        std::string filter;
        std::getline(ifs, filter);
    }
    ifs >> n;
    for(int i = 1; i<= n; i++){
        int id,dmg,vel;
        std::string name,tname;
        ifs >> id >> name >> dmg >> vel >> tname;
        TRBullet *nbl = new TRBullet;
        defaultBulletMap[name] = nbl;
        nbl -> setSpeed(vel);
        nbl -> setDamage(dmg);
        nbl -> linkCameraRect(&gCameraBox);
        nbl -> linkLevelRect(&gLevelBox);
        nbl -> linkTexture(gTextureKeyMap[tname]);
        for(int j = 0; j< 4; j++){
            int x,y,h,w;
            ifs >> x >> y >> h >> w;
            nbl -> setStaticClip({x,y,w,h}, (TRDirection)j);
            nbl -> setWidth(w);
            nbl -> setHeight(h);
        }
        std::string flg;
        ifs >> flg;
        if(flg == "yes"){
            nbl -> setAnimated(false);
            for(int j = 0; j < 4; j++){
                ifs >> name;
                nbl -> setAnimator(gAnimatorKeyMap[name], (TRDirection)j);
            }
        }else{
            nbl -> setAnimated(false);
        }
    }
    ifs.close();
}


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
                case SDLK_UP:case SDLK_w:
                    if(e.key.repeat == 0){
                        keyCnt++;
                    }
                    hero -> startMoveUp();
                    break;
                case SDLK_DOWN:case SDLK_s:
                    if(e.key.repeat == 0){
                        keyCnt++;
                    }
                    hero -> startMoveDown();
                    break;
                case SDLK_LEFT:case SDLK_a:
                    if(e.key.repeat == 0){
                        keyCnt++;
                    }
                    hero -> startMoveLeft();
                    break;
                case SDLK_RIGHT:case SDLK_d:
                    if(e.key.repeat == 0){
                        keyCnt++;
                    }
                    hero -> startMoveRight();
                    break;
                case SDLK_z:
                    if(hero->getZnum()>0){
                        flgAttackPerformed = hero -> performAttack();
                        gBgm->playMusic("Resources/Bgm/hero_battle.wav",true);
                        hero->setZnum(hero->getZnum()-1);
                    }
                    break;
                case SDLK_x:
                    hero -> fire();
                    break;
                case SDLK_c:
                    willPickupItem = true;
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

#pragma mark 执行每画幅需要的运算

void TRGameController::runFrame(){
    if (isGamePausing()) {
        //Do something about pause
        return;
    }
    if(!isGameRunning()){
        return;
    }

    //printf("HP : %d\n",hero->getHP());

    //Calculate enemy's moving
    for(std::list<TREnemy*>::iterator it = gEnemyList.begin(); it != gEnemyList.end(); it++){
        (*it) -> move();
        for(std::list<TRMapTile*>::iterator itt = gMapTileList.begin();itt != gMapTileList.end();itt++){
            if(!((*itt)->isPassBy()) && checkCollision((*it)->getBoxRect(), (*itt)->getBoxRect())){
                (*it) -> undo();
            }
        }
    }
    //Calculate Hero's moving
    hero -> move();
    for(std::list<TRMapTile*>::iterator itt = gMapTileList.begin();itt != gMapTileList.end();itt++){
        if((*itt)->getType() == TRMapTileTypeTeleport && checkCollision(hero->getBoxRect(), (*itt)->getColliderRect()))
        {
            if(keyBePicked==true)
            {
                nextMap(++mapID);
                keyBePicked = false;
                return;
            }
        }
        if(!((*itt)->isPassBy()) && checkCollision(hero->getBoxRect(), (*itt)->getColliderRect())) {
            hero -> undo();
            break;
        }
    }

    //Calculate Hero's Contact w/ Items
    if (willPickupItem) {
        for(std::list<TRItem*>::iterator it = gItemList.begin();it != gItemList.end();it++){
            if (checkCollision((*it) -> getBoxRect(), hero -> getAttackRect())) {
                if((*it)->getItemType()==TRItemKey)
                {
                    createInterface("interface/key/havegot",315,720,30,30,TRInterfaceTypeKey);
                    keyBePicked = true;
                }
                if((*it)->getItemType()==TRItemGun2)
                {
                    hero->setSandanNum(50);
                    createInterface("interface/gun2/sandanqiang",650,720,50,30,TRInterfaceTypeGUN2);
                    loadAndRenderFont(font,"Resources/MTCORSVA.ttf",28,changeIntToString(hero->getSandanNum()),textColor,700,720);
                }
                (*it) -> activate();
                delete *it;
                gItemList.erase(it);
                break;
            }
        }
    }willPickupItem = false;


    //Refocus the camera
    centerCameraByObject(hero);

    //Calculate Bullets
    //Hero firing bullets
    if(hero -> willFire()){
        createBullet(hero -> getBulletKey(), hero -> getX() + hero -> getWidth()/2, hero -> getY() + hero -> getHeight()/2, TRBulletFriendly, (TRDirection)(hero -> getDirection()));
        hero -> fireDone();
    }
    for(std::list<TREnemy*>::iterator it = gEnemyList.begin();it != gEnemyList.end();it++){
        if ((*it) -> willFire()) {
            if ((*it) -> isFollowMode()) {
                createBullet((*it)->getBulletKey(), (*it)->getX() + (*it)->getWidth()/2, (*it)->getY() + (*it)->getHeight()/2, TRBulletHostile, (TRDirection)((*it)->getDirection()));
            }else{
                for(int j = 0; j < 4; j++){
                    if ((*it)->canFireAt((TRDirection)j)) {
                        createBullet((*it)->getBulletKey(), (*it)->getX() + (*it)->getWidth()/2, (*it)->getY() + (*it)->getHeight()/2, TRBulletHostile, (TRDirection)j);
                    }
                }
            }
            (*it) -> doneFire();
        }
    }
    //Bullet itself
    for(std::list<TRBullet*>::iterator it = gBulletList.begin();it != gBulletList.end();it++){
        (*it) -> move();
        if((*it) -> getType() == TRBulletFriendly){
            //Check collide with enemy
            for(std::list<TREnemy*>::iterator itt = gEnemyList.begin();itt != gEnemyList.end();itt++){
                if(checkCollision((*it)->getBoxRect(), (*itt) -> getBoxRect())){
                    (*it) -> attackEnemy((*itt));
                    break;
                }
            }
            if((*it) -> isUsed()){
                delete *it;
                gBulletList.erase(it);
                break;
            }
        }else{
            //Check collide with hero
            if(checkCollision(hero -> getColliderRect(), (*it) -> getBoxRect())){
                (*it) -> attackHero(hero);
                delete *it;
                gBulletList.erase(it);
                break;
            }
        }

        //check collide with wall
        for(std::list<TRMapTile*>::iterator itt = gMapTileList.begin();itt != gMapTileList.end();itt++){
            if(!(*itt)->isPassBy() && checkCollision((*it) -> getBoxRect(), (*itt) -> getBoxRect())){
                delete *it;
                gBulletList.erase(it);
                break;
            }
        }
    }

    //Calculate Attacks
    if (flgAttackPerformed) {
        for(std::list<TREnemy*>::iterator it = gEnemyList.begin(); it != gEnemyList.end(); it++){
            if(checkCollision((*it)->getBoxRect(), hero->getAttackRect())){
                hero -> attack((*it));
            }
        }
        flgAttackPerformed = false;
    }

    //Calculate Being Attacks
    for(std::list<TREnemy*>::iterator it = gEnemyList.begin(); it != gEnemyList.end(); it++){
        if (checkCollision(hero->getBoxRect(), (*it)->getBoxRect())) {
            if(!(*it)->startAttacking()){
                (*it)->attack(hero, (*it)->getDamage());
            }
        }
    }

    //Delete dead Enemys
    for(std::list<TREnemy*>::iterator it = gEnemyList.begin(); it != gEnemyList.end(); it++){
        if(!(*it)->isAlive()){
            delete *it;
            gEnemyList.erase(it);
            it--;
        }
    }

    //Check Traps
    for(std::list<TRTrap*>::iterator it = gTrapList.begin();it != gTrapList.end();it++){
        if (checkCollision(hero->getBoxRect(), (*it)->getColliderRect())) {
            if( (*it) -> getType() == TRTrapSlow | TRTrapLasting && haveBeenSlow == false )
            {
                createInterface("interface/lowspeed/limittime",465,720,30,30,TRInterfaceTypeLowspeed);
                std::cerr<<"yes"<<endl;
                haveBeenSlow = true;
            }
            (*it) -> activate();
        }
    }

    //Calculate debuffs


    //Render all

    for(std::list<TRMapTile*>::iterator it = gMapTileList.begin();it != gMapTileList.end();it++){
        (*it) -> render();
    }
    for(std::list<TRBullet*>::iterator it = gBulletList.begin();it != gBulletList.end();it++){
        (*it) -> render();
    }
    for(std::list<TRItem*>::iterator it = gItemList.begin();it != gItemList.end();it++){
        (*it) -> render();
    }
    for(std::list<TRTrap*>::iterator it = gTrapList.begin();it != gTrapList.end();it++){
        (*it) -> render();
    }
    for(std::list<TRBullet*>::iterator it = gBulletList.begin(); it != gBulletList.end();it++){
        (*it) -> render();
    }
    for(std::list<TREnemy*>::iterator it = gEnemyList.begin(); it != gEnemyList.end(); it++){
        (*it) -> render();
    }
    for(std::list<TRInterface*>::iterator it = gInterfaceList.begin(); it != gInterfaceList.end(); it++){
        /*if((*it)->getInterfaceType()==TRInterfaceTypeLowspeed)
        {
            if(a==60)
            {
                (*it)->render();
                a=0;
            }
        }else if((*it)->getInterfaceType()==TRInterfaceTypeKey){
            if(b==100)
            {
                (*it)->render();
                b=0;
            }
        }*/
            if((*it)->getInterfaceType()==TRInterfaceTypeLowspeed)
            {
                if(c==0)
                {
                    delete *it;
                    gInterfaceList.erase(it);
                    haveBeenSlow = false;
                    c = 780;
                }else{
                    loadAndRenderFont(font,"Resources/MTCORSVA.ttf",32,changeIntToString(c/60),textColor,500,720);
                    c--;
                    (*it) -> render();
                }
            }
            (*it) -> render();
            a+=1;
            b+=1;
    }
    loadAndRenderFont(font,"Resources/MTCORSVA.ttf",28,"BOOM:"+changeIntToString(hero->getZnum()),textColor,800,720);
    loadAndRenderFont(font,"Resources/MTCORSVA.ttf",28,changeIntToString(hero->getTreasure()),textColor,50,720);
    loadAndRenderFont(font,"Resources/MTCORSVA.ttf",28,changeIntToString(hero->getBulletNum()),textColor,200,720);
    hero -> render();

    d++;
    if(d==1800)
    {
        d=0;
        hero->setZnum(hero->getZnum()+1);
    }

    //Render HP Gauge
    for(std::list<TREnemy*>::iterator it = gEnemyList.begin();it != gEnemyList.end();it++){
        SDL_Rect outer = {(*it)->getX()-gCameraBox.x,(*it)->getY()-5-gCameraBox.y,(*it)->getWidth(),3};
        SDL_Rect inner = {(*it)->getX()-gCameraBox.x,(*it)->getY()-5-gCameraBox.y,((*it)->getWidth()*(*it)->getHP()/((*it)->getMaxHP())),3};
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0, 0, 0xff);
        SDL_RenderFillRect(gRenderer, &inner);
        SDL_RenderDrawRect(gRenderer, &outer);
    }

    //小地图
    SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
    SDL_RenderFillRect(gRenderer,&gLeadingMapBox);
    if(!keyBePicked){
        loadAndRenderFont(font,"Resources/MTCORSVA.ttf",10,"k",textColor,keyX*3,keyY*3);
    }
    loadAndRenderFont(font,"Resources/MTCORSVA.ttf",10,"o",textColor,(outX)*3,(outY-1)*3);
    /*for(std::list<SDL_Rect*>::iterator it = gLeadingMapList.begin();it!=gLeadingMapList.end();it++){
        //SDL_SetRenderDrawColor(gRenderer,0xff,255,255,255);
        SDL_RenderFillRect(gRenderer,*it);
    }*/
    //小地图英雄定位
    heroX = hero->getX()/50;
    heroY = hero->getY()/50;
    heroLeadingPisition = {heroX*3,heroY*3,3,3};
    SDL_SetRenderDrawColor(gRenderer,0xff,0,255,0);
    SDL_RenderFillRect(gRenderer,&heroLeadingPisition);

    //Calculate hero's hp
    int hp = hero->getHP();
    int maxHp = hero->getMaxHP();
    hpRect.w = hp/(double)(maxHp/70);
    hpRect.x = hero->getX()-gCameraBox.x-15;
    hpRect.y = hero->getY()-gCameraBox.y-5;
    hpOutlineRect.x = hpRect.x;
    hpOutlineRect.y = hpRect.y;
    hpOutlineRect.w = 70;
    hpRect.h = hpOutlineRect.h = 4;
    if(hp==0)hpRect.w=0;
    SDL_SetRenderDrawColor(gRenderer,0xFF,0x00,0x00,0xFF);
    SDL_RenderFillRect(gRenderer,&hpRect);
    SDL_RenderDrawRect(gRenderer,&hpOutlineRect);

}

string TRGameController::changeIntToString(int n)
{
    sprintf(t,"%d",n);
    s = t;
    return s;
}

void TRGameController::loadAndRenderFont(TTF_Font *ft,std::string path,int fontSize,std::string text,SDL_Color textColor,int x,int y)
{
    if(font == NULL) font = TTF_OpenFont(path.c_str(),fontSize);
    if(font == NULL){
        printf("Failed to load the font!SDL_ttf Error:%s\n",TTF_GetError());
    }else{
        gTexture->linkFont(font);
        gTexture->linkRenderer(gRenderer);
        if(!gTexture->loadFromRenderedText(text,textColor)){
            printf("Failed to render text texture!\n");
        }else{
            gTexture->render(x,y);
        }
    }
    TTF_CloseFont(font),font = NULL;
}

TRGameController::TRGameController(){
    gLevelBox = {0,0,1920,1080};
    keyCnt = 0;
    hero = NULL;
    font = NULL;
    initialize();
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

#pragma mark - 创建游戏部件
#pragma mark 创建地图要素
void TRGameController::createMapTile(std::string textureKey,TRMapTileType type,int x,int y,int h,int w){
    TRMapTile *tile = new TRMapTile;
    tile -> setX(x);
    tile -> setY(y);
    tile -> setWidth(w);
    tile -> setHeight(h);
    tile -> setCurClip({0,0,w,h});
    tile -> setType(type);
    tile -> setColliderFactor(0.7);
    tile -> linkCameraRect(&gCameraBox);
    tile -> linkLevelRect(&gLevelBox);
    tile -> linkTexture(gTextureKeyMap[textureKey]);
    gMapTileList.insert(gMapTileList.end(), tile);
}
#pragma mark 创建敌人
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
#pragma mark 创建英雄
void TRGameController::createHero(std::string defaultKey,int x,int y,int h,int w){
    TRHero *hr = new TRHero;
    *hr = *defaultHeroMap[defaultKey];
    hr -> setX(x);
    hr -> setY(y);
    hr -> setHeight(h);
    hr -> setWidth(w);
    hero = hr;
}
#pragma mark 创建道具
void TRGameController::createItem(std::string defaultKey, int x, int y, int h, int w){
    TRItem *ci = new TRItem;
    *ci = *defaultItemMap[defaultKey];
    ci -> setX(x);
    ci -> setY(y);
    ci -> setHeight(h);
    ci -> setWidth(w);
    ci -> linkHero(hero);
    gItemList.insert(gItemList.end(), ci);
}
#pragma mark 创建陷阱
void TRGameController::createTrap(std::string defaultKey, int x, int y, int h, int w){
    TRTrap *ctr = new TRTrap;
    *ctr = *defaultTrapMap[defaultKey];
    ctr -> setX(x);
    ctr -> setY(y);
    ctr -> setHeight(h);
    ctr -> setWidth(w);
    ctr -> linkHero(hero);
    gTrapList.insert(gTrapList.end(), ctr);
}
#pragma mark 创建子弹
void TRGameController::createBullet(std::string defaultKey, int x, int y, TRBulletType typ,TRDirection dir){
    TRBullet *cbl = new TRBullet;
    *cbl = *defaultBulletMap[defaultKey];
    cbl -> setType(typ);
    cbl -> setDirection(dir);
    cbl -> setX(x);
    cbl -> setY(y);
    cbl -> startMoving();
    gBulletList.insert(gBulletList.end(), cbl);
}

#pragma mark 创建界面
void TRGameController::createInterface(std::string defaultKey,int x,int y,int h,int w,TRInterfaceType typ){
    TRInterface *interface = new TRInterface;
    *interface = *defaultInterfaceMap[defaultKey];
    interface->setX(x);
    interface->setY(y);
    interface->setHeight(h);
    interface->setWidth(w);
    gInterfaceList.insert(gInterfaceList.end(),interface);
}

#pragma mark 创建小地图
void TRGameController::createLeadingMapOthers(int x,int y,int h,int w){
    SDL_Rect leadingMapTileRect;
    leadingMapTileRect.x = x;
    leadingMapTileRect.y = y;
    leadingMapTileRect.h = h;
    leadingMapTileRect.w = w;
    gLeadingMapList.insert(gLeadingMapList.end(),&leadingMapTileRect);
}

#pragma mark - 游戏过程控制
#pragma mark 切换地图
void TRGameController::nextMap(int mapID)
{
    //free();
    std::string pathP1 = "Resources/Mapdata/map";
    char pathP2_[20];
    sprintf(pathP2_, "%d",mapID);
    string pathP2(pathP2_);
    std::string pathP3 = ".map";
    pauseGame();
    clearStage();
    loadMapFromFile(pathP1+pathP2+pathP3);
    loadLeadingMapFromFile(pathP1+pathP2+pathP3);
    resumeGame();
}

#pragma mark 开始游戏
void TRGameController::startGame(){
    flgGameStarted = true;
    flgGamePaused = false;
    loadMapFromFile("Resources/Mapdata/map1.map");
    loadLeadingMapFromFile("Resources/Mapdata/map1.map");
}

#pragma mark 暂停游戏
void TRGameController::pauseGame(){
    flgGamePaused = true;
}

#pragma mark 恢复游戏
void TRGameController::resumeGame(){
    flgGamePaused = false;
}

#pragma mark 检测游戏是否暂停
bool TRGameController::isGamePausing(){
    return flgGamePaused;
}

#pragma mark 检测游戏是否正在运行
bool TRGameController::isGameRunning(){
    if(flgGameStarted && !flgGamePaused){
        return true;
    }
    return false;
}

#pragma mark - 游戏设定
#pragma mark 设定屏幕（摄像机）尺寸
void TRGameController::setCamera(int h,int w){
    gCameraBox.h = h;
    gCameraBox.w = w;
}

#pragma mark 链接坐标转换器
void TRGameController::linkGrider(TRGrider *grid){
    gGrider = grid;
}

#pragma mark 链接寻路器
void TRGameController::linkPathfinder(TRPathFinder *pf){
    gPathFinder = pf;
}

#pragma mark - 辅助
#pragma mark 碰撞检测
bool TRGameController::checkCollision(SDL_Rect a, SDL_Rect b){
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

