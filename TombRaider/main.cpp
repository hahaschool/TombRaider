//
//  main.cpp
//  TombRaider
//
//  Created by 張正昊 on 12/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "TRGameController.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TRPathFinder *gPathFinder = NULL;
TRGrider *gGrider = NULL;
TRGameController *gGameController = NULL;


bool init(){
    //初始化成功标志
    bool success = true;
    
    gGameController = new TRGameController;
    
    gGrider = new TRGrider;
    
    gPathFinder = new TRPathFinder;
    
    
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("Error: SDL_Init Failed. SDL Error: %s\n",SDL_GetError());
        success = false;
    }else{
        //线性贴图过滤
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }
        //创建窗口
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL){
            printf("Error:Window creation failed. SDL_Error: %s\n",SDL_GetError());
            success = false;
        }else{
            //垂直同步
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL){
                printf("Error:Render Creation Failed.SDL_Error : %s\n",SDL_GetError());
                success = false;
            }else{
                //设定渲染器默认颜色
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                //初始化PNG载入
                int imgFlag = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlag) & imgFlag)){
                    printf("Error:SDL_image init failed.SDL_image Error: %s\n",IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

void close(){
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystem
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, const char * argv[]) {
    if (!init()) {
        printf("Error:Failed to load.\n");
    }else{
        bool quit = false;
        SDL_Event e;
        
        while(!quit){
            while (SDL_PollEvent(&e) != 0) {
                if(e.type == SDL_QUIT){
                    quit = true;
                }
                //handleEvent
                
                
                
                
            }
            
            
        }
    }
    colse();
    return 0;
}
