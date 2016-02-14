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

class TRPathFinder{
public:
    void init(int h,int w);
    bool findPath(int from,int to);
    std::vector<std::vector<int> > mat;
private:
    static const int INF = 0x3f3f3f3f;
    constexpr static const int dir[4][2] = {{1,0},{-1,0},{0,-1},{0,1}};
    std::vector<std::vector<bool> > vis;
    std::vector<std::vector<int> > h;
    std::vector<std::vector<int> > f;
    std::vector<std::vector<int> > g;
    int n,m;
    int tarX,tarY;
    int strX,strY;
    
    struct State{
        int x,y,f,g,h;
        bool operator < (const State &b) const{
            if(f == b.f){
                return g < b.g;
            }
            return f < b.f;
        }
    };
    
    bool isValid(int x,int y);
    void calculate_heuristics_manhatton();
    void calculate_heuristic_euler();
    void performAStar();
};

#endif /* TRPathFinder_hpp */
