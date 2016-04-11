//
//  TRTexture.hpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#ifndef TRTexture_hpp
#define TRTexture_hpp

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

class TRTexture{
public:
    //Constructor
    TRTexture();
    //Destructor
    ~TRTexture();
    //Load Resource Image
    bool loadFromFile(std::string path,Uint8 keyRed = 0,Uint8 keyGreen = 0xFF,Uint8 keyBlue = 0XFF);
//#ifdef _SDL_TTF_H
    //Load from TTF fonts
    bool loadFromRenderedText(std::string textureText,SDL_Color textColor);
//#endif
    //Deallocate Texture
    void free();
    //Set Blending
    void setBlendMode(SDL_BlendMode blending);
    //Set Alpha Modulation
    void setAlpha(Uint8 alpha);
    //Set Color Modulation
    void setColor(Uint8 red,Uint8 green,Uint8 blue);
    //Render Texture at x,y Clipped at Rect given, w/ Rotation anf Filp
    void render(int x,int y,SDL_Rect *clip = NULL,double angle = 0, SDL_Point *center = NULL,SDL_RendererFlip flip = SDL_FLIP_NONE);
    //Image Diminsions Getter
    int getWidth();
    int getHeight();
    void linkRenderer(SDL_Renderer *renderer);
    void linkFont(TTF_Font *font);

private:
    //Linked Renderer
    SDL_Renderer *mRenderer;

    //SDL Texture
    SDL_Texture *mTexture;

//#ifdef _SDL_TTF_H
    TTF_Font *mFont;
//#endif

    //Image Diminsions
    int mWidth;
    int mHeight;
};

#endif /* TRTexture_hpp */
