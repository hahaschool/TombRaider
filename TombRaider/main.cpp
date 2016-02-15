//
//  main.cpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include <iostream>
#include "TRPathFinder.hpp"

int main(int argc, const char * argv[]) {
    int n,m,a,b,c,d;
    std::cin >> n >> m >> a >> b >> c >> d;
    TRPathFinder pf;
    pf.init(n, m, 3);
    pf.setHeuristic(TRPathFinderHeuristicManhatton);
    pf.setStartingPoint(b, a);
    pf.setTargetPoint(d, c);
    for(int i = 0;i < n; i++){
        for(int j = 0;j < m; j++){
            char q;
            scanf(" %c",&q);
            if(q == '0'){
                pf.setMatrix(j, i, TRPathFinderMatrixObstacle);
            }else{
                pf.setMatrix(j, i, TRPathFinderMatrixRoad);
            }
        }
    }
    pf.findPath();
    pf.printOut();
    return 0;
}
