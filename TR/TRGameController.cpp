//
//  TRGameController.cpp
//  TombRaider
//
//  Created by 張正昊 on 13/2/2016.
//  Copyright © 2016 hahaschool. All rights reserved.
//

#include "TRGameController.hpp"

TRGameController::TRGameController(){
    
}

TRGameController::~TRGameController(){
    free();
}

void TRGameController::free(){
    
}

void TRGameController::loadResources(){
    
}

void TRGameController::handleEvent(SDL_Event &e){
    if(!(hero->isMoving()))
	{
		heroStaticImage = keyBoard.staticDirections(e)
	}
	//Apply the current image
	hero->render();
}

void TRGameController::centerCameraByObject(TRObject *obj){
    gCameraBox.x = (obj->getX() + obj->getWidth()) - gCameraBox.w/2;
    gCameraBox.y = (obj->getY() + obj->getHeight()) - gCameraBox.h/2;
    if(gCameraBox.x < 0){
        gCameraBox.x = 0;
    }
    if(gCameraBox.y < 0){
        gCameraBox.y = 0;
    }
    if (gCameraBox.x > gLevelBox.w - gCameraBox.w) {
        gCameraBox.x = gLevelBox.w - gCameraBox.w;
    }
    if(gCameraBox.y > gLevelBox.h - gCameraBox.h){
        gCameraBox.y = gLevelBox.h - gCameraBox.h;
    }
}

void TRGameController::linkRenderer(SDL_Renderer *renderer){
    gRenderer = renderer;
}

void TRGameController::createMapTile(std::string textureKey,TRMapTileType type,int x,int y){
    
}

void TRGameController::createEnemy(){
    
}

void TRGameController::startGame(){
    
}

void TRGameController::pauseGame(){
    
}

void TRGameController::resumeGame(){
    
}

bool TRGameController::isGamePausing(){
    return flgGamePaused;
}

bool TRGameController::isGameRunning(){
    if(flgGameStarted && !flgGamePaused){
        return true;
    }
    return false;
}

bool TRGameController::checkCollision(SDL_Rect a, SDL_Rect b){
        //The sides of the rectangles
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;
        
        //Calculate the sides of rect A
        leftA = a.x;
        rightA = a.x + a.w;
        topA = a.y;
        bottomA = a.y + a.h;
        
        //Calculate the sides of rect B
        leftB = b.x;
        rightB = b.x + b.w;
        topB = b.y;
        bottomB = b.y + b.h;
        
        //If any of the sides from A are outside of B
        if( bottomA <= topB ){
            return false;
        }
        if( topA >= bottomB ){
            return false;
        }
        if( rightA <= leftB ){
            return false;
        }
        if( leftA >= rightB ){
            return false;
        }
        
        //If none of the sides from A are outside B
        return true;
}




