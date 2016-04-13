#include "TRLeadingMap.h"
TRLeadingMap::TRLeadingMap(){
}

void TRLeadingMap::loadMap(std::string path)
{
    std::ifstream ifs;
    ifs.open(path);
    int n,m;
    ifs >> n >> m;
    leadingMapBox.h = n*2;
    leadingMapBox.w = n*2;
    for(int i = 0; i<n;i++){
        for(int j=0;j<m;j++)
        {
            char a;
            ifs >> a;
            switch(a){
           case 'o':
            createLeadingMapTile("leadingMap/out");
            break;
            }
        }
    }
}
