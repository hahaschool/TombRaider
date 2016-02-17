//
//  TRTexture.cpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRTexture.hpp"

TRTexture::TRTexture(){
#ifdef _SDL_TTF_H
    mFont = NULL;
#endif
    mRenderer = NULL;
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

TRTexture::~TRTexture(){
    free();
}

bool TRTexture::loadFromFile(std::string path,Uint8 keyRed,Uint8 keyGreen,Uint8 keyBlue){
    //Clear loaded texture
    free();
    //Load texture via surface
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }else{
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, keyRed, keyGreen, keyBlue));
        mTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
        if(mTexture == NULL){
            printf("Failed to create texture from %s! SDL_Error: %s\n",path.c_str(),SDL_GetError());
        }else{
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool TRTexture::loadFromRenderedText(std::string renderedText, SDL_Color textColor){
    free();
    SDL_Surface *loadedSurface = TTF_RenderText_Solid(mFont, renderedText.c_str(), textColor);
    if(loadedSurface == NULL){
        //EXCEPTION
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }else{
        mTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
        if(mTexture == NULL){
            //EXCEPTION
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }else{
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
    }
    return mTexture != NULL;
}
#endif

void TRTexture::free(){
    if(mTexture != NULL){
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void TRTexture::setColor(Uint8 red,Uint8 green,Uint8 blue){
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void TRTexture::setBlendMode(SDL_BlendMode blend){
    SDL_SetTextureBlendMode(mTexture, blend);
}

void TRTexture::setAlpha(Uint8 alpha){
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void TRTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    //Set clip rendering dimensions
    if( clip != NULL ){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    //Render to screen
    SDL_RenderCopyEx( mRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int TRTexture::getWidth(){
    return mWidth;
}

int TRTexture::getHeight(){
    return mHeight;
}

void TRTexture::linkRenderer(SDL_Renderer *renderer){
    mRenderer = renderer;
}

#ifdef _SDL_TTF_H
void TRTexture::linkFont(TTF_Font *font){
    mFont = font;
}
#endif
