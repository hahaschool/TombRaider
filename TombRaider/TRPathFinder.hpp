//
//  TRPathFinder.hpp
//  TombRaider
//
//  Created by 張正昊 on 14/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRPathFinder_hpp
#define TRPathFinder_hpp

#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <cmath>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>

//使用方法：
//1.使用init()初始化好寻路器
//2.使用setMatrix()配置好图
//3.使用setHeuristic()配置A*工作模式
//4.使用setStartingPoint(),setTargetPoint()配置起点终点
//5.findPath()寻路
//6.提取路径
//注意：更换起终点之前的步骤都不用重复执行

enum TRPathFinderHeuristic{
    //曼哈顿距离
    TRPathFinderHeuristicManhatton = 1,
    //欧拉距离
    TRPathFinderHeuristicEuler = 2,
    //SPFA预处理，求k短路时需要使用此项
    TRPathFinderHeuristicSPFA = 3,
    //直接令A*工作成SPFA
    TRPathFinderHeuristicNone = 0
};

enum TRPathFinderMatrix{
    //不可行块
    TRPathFinderMatrixObstacle = 0,
    //可行块
    TRPathFinderMatrixRoad = 1
};

class TRPathFinder{
public:
    //初始化
    void init(int h,int w,int initDValue);
    //寻找从str到tar的路径，返回是否找到，路径保存在一个stack里
    bool findPath();
    //设定A*算法使用的启发函数
    void setHeuristic(TRPathFinderHeuristic heu);
    //当前使用的启发函数类型
    TRPathFinderHeuristic getHeuristic();
    //强制重算评估函数
    void calculateHeuristic(bool force = false);
    //修改迷宫矩阵
    void setMatrix(int x,int y,TRPathFinderMatrix a);
    //起点终点的setter和getter
    void setStartingPoint(int x,int y);
    void setTargetPoint(int x,int y);
    int getStartingPointX();
    int getStartingPointY();
    int getTargetPointX();
    int getTargetPointY();
    
    //启发函数比重
    void setDValue(int x,int y,int nd);
    void setDValueAll(int nd);
    int getDValue(int x,int y);
    
    //提取路径(每一次返回stk头，栈空时返回false)
    /*
     使用例：
     while(extractPath(a,b));
     */
    bool extractPath(int &topX,int &topY);
    
    //Debug
    void printOut();
    
private:
    const static int INF = 0x3f3f3f3f;
    //表示图的矩阵
    std::vector<std::vector<int> > mat;
    std::vector<std::vector<bool> > vis;
    std::vector<std::vector<int> > h;
    std::vector<std::vector<int> > f;
    std::vector<std::vector<int> > g;
    std::vector<std::vector<int> > d;
    std::vector<std::vector<int> > parX;
    std::vector<std::vector<int> > parY;
    
    int n,m;
    int heuX,heuY;
    int tarX,tarY;
    int strX,strY;
    int heuristic;
    std::stack<std::pair<int,int> > stk;
    struct State{
        int x,y,f,g,h;
        bool operator < (const State &b) const{
            if(f == b.f){
                return g > b.g;
            }
            return f > b.f;
        }
    };
    
    bool isValid(int x,int y);
    int dis_manhatton(int x1,int y1,int x2,int y2);
    int dis_euler(int x1,int y1,int x2,int y2);
    void calculate_heuristics_manhatton();
    void calculate_heuristic_euler();
    //void calculate_heuristic_SPFA();
    bool performAStar();
    
    
};

#endif /* TRPathFinder_hpp */
