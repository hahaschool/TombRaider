#ifndef TRLEADINGMAP_H_INCLUDED
#define TRLEADINGMAP_H_INCLUDED
#include "TRTexture.hpp"
class TRLeadingMap{
public:
    TRLeadingMap();
    ~TRLeadingMap();
    void loadMap(std::string path);

private:
    SDL_Rect leadingMapBox;
};


#endif // TRLEADINGMAP_H_INCLUDED
