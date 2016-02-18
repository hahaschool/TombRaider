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
	//����ֹʱ��ת��
	SDL_Surface staticDirections(SDL_Event &event);
	//�����˶�ʱ�ķ���
	SDL_Surface moveDirections(SDL_Event &event);
	//��������ʽ
    SDL_Surface attackMethods(SDL_Event &event);
	//����������Ϊ
	bool otherActions(SDL_Event &event);
	//����ͼƬ
	SDL_Surface* loadSurface( std::string path );
	//����Ӣ�۾�ֹͼƬ
	bool loadHeroStaticImages();
private:
	//��ֹʱ��ת��
	int staticDirection;
	//�˶�ʱ����
	int moveDirection;
	//������ʽ
	int attackMethod;
	//������Ϊ
	int otherAction;
	//�¼�
	SDL_Event event;
	//Ӣ�۶���
	TRHero hero;
	//Ӣ��ͼ��
	TRTexture* staticSurfaces[TR_Hero_Static_Image];
	TRTexture* moveSurfaces[TR_Hero_Move_Image];
	TRTexture* heroStaticSurface;
	TRTexture* heroMoveSurface;
};
