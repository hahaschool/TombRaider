//
//  TRPathFinder.cpp
//  TombRaider
//
//  Created by 張正昊 on 14/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRPathFinder.hpp"

void TRPathFinder::init(int mapHeight,int mapWidth){
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
        f.emplace_back(singleRow);
        h.emplace_back(singleRow);
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


bool TRPathFinder::isValid(int x, int y){
    if(x < 0 || y < 0 || x >= m || y >= n){
        return false;
    }
    return true;
}

void TRPathFinder::performAStar(){
    std::priority_queue<State> que;
    State nxt;
    
    
}

void TRPathFinder::calculate_heuristic_euler(){
    
}