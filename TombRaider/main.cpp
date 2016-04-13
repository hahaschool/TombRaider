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
#include "TRBgm.h"
#include <ctime>
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 750;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const int BLOOD_LENGTH = 300;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TRPathFinder *gPathFinder = NULL;
TRGrider *gGrider = NULL;
TRGameController *gGameController = NULL;
TRBgm *gBgm = NULL;
SDL_Surface* gScreenScreen = NULL;
SDL_Surface* gStartScreen = NULL;
SDL_Surface* gEndScreen = NULL;
SDL_Surface* gWinScreen = NULL;

const char* ButtonFile[]={};
SDL_Surface* ButtonSur=NULL;
SDL_Texture* ButtonText=NULL;

SDL_Rect StartButtonRect = {400,450,100,50};
SDL_Rect PauseButtonRect = {400,550,100,50};
SDL_Rect ExitButtonRect = {400,650,100,50};
SDL_Event Mouse;

using namespace std;

bool UpdateButton(Uint32);
bool isOnStartButton(Uint32,Uint32);
bool isOnPauseButton(Uint32,Uint32);
bool isOnExitButton(Uint32,Uint32);
bool drawStartBackGround();
void halt();

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
            gScreenScreen = SDL_GetWindowSurface(gWindow);
            //垂直同步
            gRenderer = SDL_GetRenderer(gWindow);
            if(gRenderer == NULL){
                printf("Error:Render Creation Failed.SDL_Error : %s\n",SDL_GetError());
                success = false;
            }else{
                //设定渲染器默认颜色
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
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
                if(TTF_Init()==-1)
                {
                    printf("SDL_ttf could not initialize!SDL_ttf error: %s\n",TTF_GetError());
                    success = false;
                }

            }
        }
    }

    gStartScreen = SDL_LoadBMP("Resources/Texture/Maptile/begin.bmp");
    gEndScreen = SDL_LoadBMP("Resources/Texture/Maptile/fail.bmp");
    gWinScreen = SDL_LoadBMP("Resources/Texture/Maptile/win.bmp");
    if(gStartScreen == NULL)
    {
        printf("Unable to load start image!",SDL_GetError());
    }
    if(gEndScreen == NULL)
    {
        printf("Unable to load end image!",SDL_GetError());
    }
    if(gWinScreen == NULL)
    {
        printf("Unable to load win image!",SDL_GetError());
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
    //free surface
    SDL_FreeSurface(gStartScreen);
    SDL_FreeSurface(gEndScreen);
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystem
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void halt(){
    cerr<<SDL_GetError()<<endl;
    close();
    exit(-1);
}

int main(int argc,char * argv[]) {
    srand(time(NULL));
    if (!init()) {
        printf("Error:Failed to load.\n");
    }else{
        bool quit = false;
        SDL_Event e;

        SDL_BlitSurface(gStartScreen,NULL,gScreenScreen,NULL);
        SDL_UpdateWindowSurface(gWindow);
        gBgm->playMusic("Resources/Bgm/阴森.wav",true);
        SDL_Delay(4000);


        gGameController -> startGame();
        /*
        //PRESSURE TEST BLK
        for(int i = 1; i <= 10000;i++){
            gGameController->createEnemy("bat", 101+rand()%50, 101+rand()%50, 50, 50);
        }
         */
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
            if(gGameController->isGameFail()==true){
                SDL_BlitSurface(gEndScreen,NULL,gScreenScreen,NULL);
                SDL_UpdateWindowSurface(gWindow);
                SDL_Delay(4000);
                quit = true;
            }
            if(gGameController->isGameWin()==true){
                SDL_BlitSurface(gWinScreen,NULL,gScreenScreen,NULL);
                SDL_UpdateWindowSurface(gWindow);
                SDL_Delay(4000);
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
