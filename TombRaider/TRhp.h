#ifndef TRHP_H_INCLUDED
#define TRHP_H_INCLUDED

#include "TRObject.hpp"
#include "TRHero.hpp"
class TRhp:public TRObject{
private:
    int hp;
    TRHero *gHero;
public:
    TRhp();
    int getHp();
    void drawHPBar();
};
#endif // TRHP_H_INCLUDED
