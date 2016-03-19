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
#include "TRTimer.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

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
    
    
    
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ){
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }else{
        //线性贴图过滤
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }
        //创建窗口
        gWindow = SDL_CreateWindow("Tomb Raider", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }

            }
        }
    }

    gGameController -> linkRenderer(gRenderer);
    gGameController -> setCamera(SCREEN_HEIGHT, SCREEN_WIDTH);
    gGameController -> linkGrider(gGrider);
    gGameController -> linkPathfinder(gPathFinder);
    gGameController -> loadResources();
    
    gGrider -> tileHeight = 50;
    gGrider -> tileWidth = 50;
    
    gPathFinder -> setHeuristic(TRPathFinderHeuristicEuler);
    
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
    srand(time(NULL));
    if (!init()) {
        printf("Error:Failed to load.\n");
    }else{
        bool quit = false;
        SDL_Event e;
        
        //dubug
        gGameController -> createHero("hahaschool", 50, 50, 48, 32);
        gGameController->loadMapFromFile("Resources/Mapdata/test.map");
        for(int i = 1; i <= 10; i++){
            for(int j = 1; j<= 10; j++){
                gGameController -> createEnemy("bat", 10*i+50, 10*j+50, 50, 50);
            }
        }
        
        
        gGameController -> startGame();
        
        //The frames per second timer
        TRTimer fpsTimer;
        
        //The frames per second cap timer
        TRTimer capTimer;
        
        //Start counting frames per second
        int countedFrames = 0;
        fpsTimer.start();
        
        while(!quit){
            //Start cap timer
            capTimer.start();
            if(gGameController -> isGameRunning() == false){
                quit = true;
            }
            gGameController -> handleEvent(e);
            //Calculate and correct fps
            float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
            if( avgFPS > 2000000 )
            {
                avgFPS = 0;
            }
            
            
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
            gGameController -> runFrame();
            SDL_RenderPresent( gRenderer );
            
            //If frame finished early
            int frameTicks = capTimer.getTicks();
            if( frameTicks < SCREEN_TICK_PER_FRAME )
            {
                //Wait remaining time
                SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
            }
        }
    }
    close();
    return 0;
}
