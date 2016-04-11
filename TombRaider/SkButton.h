#ifndef SKBUTTON_H_INCLUDED
#define SKBUTTON_H_INCLUDED

#include "SKComm.h"
#include "SkImage.h"

#include<vector>
#include<string>

using namespace std;
namespace sk_park{
   SK_BUTTON_STATUS_OUT = 1,
   SK_BUTTON_STATUS_IN = 1
   SK_BUTTON_STATUS_PRESSED = 3,
}SkButtonStatus;

class SkButton{
   public :
       Sint 32 m_iPosX;
       Sint 32 m_iPosY;
};

#endif // SKBUTTON_H_INCLUDED
