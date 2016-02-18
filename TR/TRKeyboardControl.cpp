#include "TRKeyboardControl.h"

SDL_Surface* loadSurface( std::string path )
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}

	return loadedSurface;
}

bool TRKeyboardControl::loadHeroStaticImages(){
	//Loading success flag
	bool success = true;

	//Load up surface
	staticSurfaces[KEY_STATIC_UP] = loadSurface("image/up.bmp");
	if( staticSurfaces[KEY_STATIC_UP] == NULL )
	{
		printf( "Failed to load up image!\n" );
		success = false;
	}
	//Load down surface
	staticSurfaces[KEY_STATIC_DOWN] = loadSurface("image/down.bmp");
	if( staticSurfaces[KEY_STATIC_DOWN] == NULL )
	{
		printf( "Failed to load down image!\n" );
		success = false;
	}
	//Load left surface
	staticSurfaces[KEY_STATIC_LEFT] = loadSurface("image/left.bmp");
	if( staticSurfaces[KEY_STATIC_LEFT] == NULL )
	{
		printf( "Failed to load left image!\n" );
		success = false;
	}
	//Load right surface
	staticSurfaces[KEY_STATIC_RIGHT] = loadSurface("image/right.bmp");
	if( staticSurfaces[KEY_STATIC_RIGHT] == NULL )
	{
		printf( "Failed to load right image!\n" );
		success = false;
	}

}

SDL_Surface TRKeyboardControl:: staticDirections(SDL_Event event){
	switch(event.key.keysym.sym)
	{
	case SDLK_UP:
		staticDirection = KEY_STATIC_UP;
		heroStaticSurface = staticSurfaces[staticDirection];
		break;
	case SDLK_DOWN:
		staticDirection = KEY_STATIC_DOWN;
		heroStaticSurface = staticSurfaces[staticDirection];
		break;
	case SDLK_LEFT:
		staticDirection = KEY_STATIC_LEFT;
		heroStaticSurface = staticSurfaces[staticDirection];

		break;
	case SDLK_RIGHT:
		staticDirection = KEY_STATIC_RIGHT;
		heroStaticSurface = staticSurfaces[staticDirection];
		break;
	case SDLK_w:
		staticDirection = KEY_STATIC_UP;

		break;
	case SDLK_s:
		staticDirection = KEY_STATIC_DOWN;

		break;
	case SDLK_a:
		staticDirection = KEY_STATIC_LEFT;

		break;
	case SDLK_d:
		staticDirection = KEY_STATIC_RIGHT;

		break;
	}
	return heroStaticSurface;
}

SDL_Surface TRKeyboardControl::moveDirections(){
	switch(event.key.keysym.sym)
	{
		//�����ƶ�
	case SDLK_UP:
		moveDirection = KEY_MOVE_UP;

		break;
		//�����ƶ�
	case SDLK_DOWN:
		moveDirection = KEY_MOVE_DOWN;

		break;
		//�����ƶ�
	case SDLK_LEFT:
		moveDirection = KEY_MOVE_LEFT;

		break;
		//�����ƶ�
	case SDLK_RIGHT:
		moveDirection = KEY_MOVE_RIGHT;

		break;
		//w���������ƶ�
	case SDLK_w:
		moveDirection = KEY_MOVE_UP;

		break;
		//s���������ƶ�
	case SDLK_s:
		moveDirection = KEY_MOVE_DOWN;

		break;
		//a���������ƶ�
	case SDLK_a:
		moveDirection = KEY_MOVE_LEFT;

		break;
		//d���������ƶ�
	case SDLK_d:
		moveDirection = KEY_MOVE_RIGHT;

		break;
	}
}

SDL_Surface TRKeyboardControl::attackMethods(){
	switch(event.key.keysym.sym){
		//f������ȭ
	case SDLK_f:
		attackMethod = KEY_ATTACK_BY_FIST;

		break;
		//l��������
	case SDLK_l:
		attackMethod = KEY_ATTACK_BY_LEG;

		break;
		//k����ʹ��
	case SDLK_k:
		attackMethod = KEY_ATTACK_BY_SWORD;

		break;
		//g������ǹ
	case SDLK_g:
		attackMethod = KEY_ATTACK_BY_GUN;

		break;
	}
}

bool TRKeyboardControl::otherActions(){
	switch(event.key.keysym.sym){
		//r�������ӵ�
	case SDLK_r:
		otherAction = KEY_ADD_BULLETS;

		break;
		//b������Ѫ
	case SDLK_b: 
		otherAction = KEY_ADD_BLOOD;

		break;
		//p������ʰ�Ʊ�
	case SDLK_p:
		otherAction = KEY_PIACK_TROUSURE;

		break;
	}
}