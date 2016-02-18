#ifndef TRKeyboardControl.h
#define TRKeyboardControl.h

#include "TRHero.hpp"
#include "TREnemy.hpp"
#include "TRGrider.hpp"
#include "TRSprite.hpp"
#include "TRTexture.hpp"

#define TR_Hero_Static_Image 5
#define TR_Hero_Move_Image 4
enum KeyStaticDirections{
	KEY_STATIC_DEFAULT,
	KEY_STATIC_UP,
	KEY_STATIC_DOWN,
	KEY_STATIC_LEFT,
	KEY_STATIC_RIGHT
};
enum KeyMoveDirection{
	KEY_MOVE_DEFAULT,
	KEY_MOVE_UP,
	KEY_MOVE_DOWN,
	KEY_MOVE_LEFT,
	KEY_MOVE_RIGHT,
};
enum KeyAttackActions{
	KEY_ATTACK_BY_FIST,
	KEY_ATTACK_BY_LEG,
	KEY_ATTACK_BY_SWORD,
	KEY_ATTACK_BY_GUN
};
enum KeyOtherActions{
	KEY_PIACK_TROUSURE,
	KEY_ADD_BLOOD,
	KEY_ADD_BULLETS
};

class TRKeyboardControl{
public:
	//Contructor
	TRKeyboardControl();
	//Destructor
	~TRKeyboardControl();
	//处理静止时的转向
	SDL_Surface staticDirections(SDL_Event &event);
	//处理运动时的方向
	SDL_Surface moveDirections(SDL_Event &event);
	//处理攻击方式
    SDL_Surface attackMethods(SDL_Event &event);
	//处理其他行为
	bool otherActions(SDL_Event &event);
	//加载图片
	SDL_Surface* loadSurface( std::string path );
	//加载英雄静止图片
	bool loadHeroStaticImages();
private:
	//静止时的转向
	int staticDirection;
	//运动时方向
	int moveDirection;
	//攻击方式
	int attackMethod;
	//其他行为
	int otherAction;
	//事件
	SDL_Event event;
	//英雄对象
	TRHero hero;
	//英雄图像
	TRTexture* staticSurfaces[TR_Hero_Static_Image];
	TRTexture* moveSurfaces[TR_Hero_Move_Image];
	TRTexture* heroStaticSurface;
	TRTexture* heroMoveSurface;
};
