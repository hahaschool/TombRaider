//
//  TRPathFinder.cpp
//  TombRaider
//
//  Created by 張正昊 on 14/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRPathFinder.hpp"

void TRPathFinder::init(int mapHeight,int mapWidth,int initDValue){
    heuX = heuY = -1;
    n = mapHeight , m = mapWidth;
    mat.clear();
    h.clear();
    g.clear();
    f.clear();
    std::vector<int> singleRow;
    for(int i = 1; i <= m; i++){
        singleRow.emplace_back(0);
    }
    for(int i = 1; i <= n ; i++){
        mat.emplace_back(singleRow);
        h.emplace_back(singleRow);
        parX.emplace_back(singleRow);
        parY.emplace_back(singleRow);
    }
    singleRow.clear();
    for(int i = 1; i <= m; i++){
        singleRow.emplace_back(initDValue);
    }
    for(int i = 1; i <= n ; i++){
        d.emplace_back(singleRow);
    }
    singleRow.clear();
    for(int i = 1; i <= m; i++){
        singleRow.emplace_back((int)INF);
    }
    for(int i = 1; i <= n ; i++){
        f.emplace_back(singleRow);
        g.emplace_back(singleRow);
    }
    vis.clear();
    std::vector<bool> singleBoolRow;
    for(int i = 1; i <= m; i++){
        singleBoolRow.push_back(false);
    }
    for(int i = 1; i <= n; i++){
        vis.push_back(singleBoolRow);
    }
}

void TRPathFinder::setDValue(int x,int y,int nd){
    d[y][x] = nd;
    h[y][x] = d[y][x] * dis_manhatton(x, y, tarX, tarY);
}
void TRPathFinder::setDValueAll(int nd){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            d[i][j] = nd;
        }
    }
    calculateHeuristic(true);
}

int TRPathFinder::getDValue(int x,int y){
    return d[y][x];
}


void TRPathFinder::setHeuristic(TRPathFinderHeuristic heu){
    heuristic = heu;
    heuX = -1,heuY = -1;
}

TRPathFinderHeuristic TRPathFinder::getHeuristic(){
    return (TRPathFinderHeuristic)heuristic;
}

void TRPathFinder::calculateHeuristic(bool force){
    if(!force && tarX == heuX && tarY == heuY){
        return;
    }
    heuX = tarX,heuY = tarY;
    if(heuristic == TRPathFinderHeuristicManhatton){
        calculate_heuristics_manhatton();
    }else if(heuristic == TRPathFinderHeuristicEuler){
        calculate_heuristic_euler();
    }else if(heuristic == TRPathFinderHeuristicSPFA){
        //calculate_heuristic_SPFA();
    }
}

void TRPathFinder::setMatrix(int x, int y, TRPathFinderMatrix a){
    mat[y][x] = a;
}

void TRPathFinder::setStartingPoint(int x,int y){
    strX = x,strY = y;
}

void TRPathFinder::setTargetPoint(int x,int y){
    tarX = x,tarY = y;
}

int TRPathFinder::getStartingPointX(){
    return strX;
}

int TRPathFinder::getStartingPointY(){
    return strY;
}

int TRPathFinder::getTargetPointX(){
    return tarX;
}

int TRPathFinder::getTargetPointY(){
    return tarY;
}

bool TRPathFinder::findPath(){
    calculateHeuristic();
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            vis[i][j] = false;
            g[i][j] = (int)INF;
        }
    }
    if(!performAStar()){
        return false;
    }
    while(!stk.empty()){
        stk.pop();
    }
    int curX = tarX,curY = tarY;
    while(curX != strX || curY != strY){
        stk.push(std::make_pair(curX, curY));
        int ncx = parX[curY][curX];
        curY = parY[curY][curX];
        curX = ncx;
    }
    stk.push(std::make_pair(curX, curY));
    return true;
}


bool TRPathFinder::isValid(int x, int y){
    if(x < 0 || y < 0 || x >= m || y >= n || mat[y][x] == TRPathFinderMatrixObstacle){
        return false;
    }
    return true;
}

bool TRPathFinder::performAStar(){
    int dir[4][2] = {{1,0},{-1,0},{0,-1},{0,1}};
    std::priority_queue<State> que;
    State cur,nxt;
    cur.x = strX,cur.y = strY;
    cur.g = 0,cur.h = h[cur.y][cur.x],cur.f = cur.g+cur.h;
    que.push(cur);
    while (!que.empty()) {
        cur = que.top();
        que.pop();
        if (cur.x == tarX && cur.y == tarY) {
            return true;
        }
        vis[cur.y][cur.x] = true;
        for(int i = 0 ; i< 4; i++){
            nxt.x = cur.x + dir[i][0];
            nxt.y = cur.y + dir[i][1];
            if(isValid(nxt.x, nxt.y)){
                nxt.g = cur.g + 1;
                nxt.h = h[nxt.y][nxt.x];
                nxt.f = nxt.g + nxt.h;
                if(nxt.g < g[nxt.y][nxt.x]){
                    g[nxt.y][nxt.x] = nxt.g;
                    f[nxt.y][nxt.x] = nxt.f;
                    parX[nxt.y][nxt.x] = cur.x;
                    parY[nxt.y][nxt.x] = cur.y;
                    que.push(nxt);
                }
            }
        }
    }
    return false;
}

int TRPathFinder::dis_manhatton(int x1,int y1,int x2,int y2){
    return std::abs(x1-x2)+std::abs(y1-y2);
}

int TRPathFinder::dis_euler(int x1, int y1, int x2, int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void TRPathFinder::calculate_heuristics_manhatton(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            h[i][j] = d[i][j]*dis_manhatton(i, j, tarX, tarY);
        }
    }
}

void TRPathFinder::calculate_heuristic_euler(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            h[i][j] = d[i][j]*dis_euler(i, j, tarX, tarY);
        }
    }
}

bool TRPathFinder::extractPath(int &topX, int &topY){
    if(stk.empty()){
        return false;
    }
    topX = stk.top().first;
    topY = stk.top().second;
    stk.pop();
    return true;
}

void TRPathFinder::printOut(){
    for(int i = 0; i < n; i++){
        for(int j = 0;j < m; j++){
            if(j == strX && i == strY){
                std::cerr << 'S';
                continue;
            }
            if(j == tarX && i == tarY){
                std::cerr << 'T';
                continue;
            }
            if (vis[i][j]) {
                std::cerr << '*';
                continue;
            }
            std::cerr << mat[i][j];
        }
        std::cerr << std::endl;
    }
    
    while (!stk.empty()) {
        std::cerr << stk.top().second << ' ' << stk.top().first << std::endl;
        stk.pop();
    }
    
}

