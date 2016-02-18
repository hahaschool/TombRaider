//
//  TRObject.hpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRObject_hpp
#define TRObject_hpp

#include <stdio.h>
#include "TRTexture.hpp"
#include "TRAnimator.hpp"
#include <string>
#include <vector>


class TRObject{
public:
    //渲染用Rect的Setter和Getter
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    SDL_Rect getBoxRect();
    void setX(int x);
    void setY(int y);
    void setWidth(int w);
    void setHeight(int h);
    void setBoxRect(SDL_Rect newBox);
    void setPos(int x,int y);
    void linkLevelRect(SDL_Rect* lvlrect);
    void linkCameraRect(SDL_Rect* camrect);
    
    //设定即将渲染的贴图资源位置
    void setCurClip(SDL_Rect clipRect);
    
    //渲染
    void render();
    //连接TRTexture
    void linkTexture(TRTexture *texture);
private:
    //连接的TRTexture,这个Texture应该包括了这个物体对应的全部资源
    TRTexture *mTexture;
    //当前正在渲染的贴图资源位置
    SDL_Rect curClip;
    //渲染时使用的Rect
    SDL_Rect mBox;
protected:
    //镜头范围
    SDL_Rect *camRect;
    //关卡范围(此处x,y取值没有关系)
    SDL_Rect *levelRect;
    
};


#endif /* TRObject_hpp */
