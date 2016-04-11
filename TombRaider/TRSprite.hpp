//
//  TRSprite.hpp
//  TombRaider
//
//  Created by 張正昊 on 13/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRSprite_hpp
#define TRSprite_hpp

#include <stdio.h>
#include "TRObject.hpp"

enum TRDirection{
    TRDirectionUp = 0,
    TRDirectionLeft = 1,
    TRDirectionDown = 2,
    TRDirectionRight = 3
};

class TRSprite : public TRObject{
public:
    //Constructor
    TRSprite();
    
    //移动速度的Setter和Getter
    void setVelX(int velX);
    void setVelY(int velY);
    void setVelXY(int velXY);
    int getVelX();
    int getVelY();
    
    //朝向的Setter和Getter
    void setDirection(int dir);
    int getDirection();
    
    //动画标志
    bool isMovingAnimated();
    bool isStaticAnimated();
    void setMovingAnimated(bool flg);
    void setStaticAnimated(bool flg);
    
    //连接TRAnimator
    void linkMovingAnimator(TRAnimator *animator,TRDirection dir);
    void linkStaticAnimator(TRAnimator *animator,TRDirection dir);
    
    //冻结移动/解除冻结
    void freeze();
    void defreeze();
    bool isFreezing();
    
    //移动位置
    void move();
    void undo();
    
    //移动中标志
    void startMoving();
    void endMoving();
    bool isMoving();
    
    //静态贴图设定
    void setStaticClip(SDL_Rect clipRect,TRDirection dir);
    
    //渲染
    void render();
protected:
    bool undoed;
private:
    
    //碰撞检测时使用的判定点Rect
    SDL_Rect mCollisionBox;
    //X/Y轴向移动速度,每帧
    int mVelX,mVelY;
    //物体当前朝向
    int mDirection;
    //不同朝向对应的静态时贴图(当禁用动画时才套用)
    SDL_Rect mStaticClip[4];
    //物体的移动状态是否动画化的标志
    bool flgMovingAnimated;
    //物体的静止状态动画化的标志
    bool flgStaticAnimated;
    //不同朝向移动对应的TRAnimator
    TRAnimator *mMovingAnimator[4];
    //不同朝向静止状态对应的TRAnimator
    TRAnimator *mStaticAnimator[4];
    //冻结标志
    bool flgFreeze;
    //移动中
    bool flgMoving;
};

#endif /* TRSprite_hpp */
