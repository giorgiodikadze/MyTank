#pragma once
#include "MoveableBlock.h"
#include "MapBlock.h"
#include <list>
#include "Bullet.h"
using namespace std;

class GTank :
	public MoveableBlock
{
public:
	GTank(short _x, short _y, short _type, short _direction=UP, short _speed=1);
	~GTank(void);

	void Draw(HDC &hdc);
	void Move(short direction = -1);
	void Fire();
	bool willHitMap();
	void DrawAndDealBullet(HDC &hDC);
	bool bulletHitTank();
	void Reset(short _x, short _y, short _direction);


	short frame;
	static const int TANK_BLOCK_WIDTH = 32;
	static const int BULLET_NUM = 1;
	short bullet_real_num;
	list<Bullet*> player_bullet;
	
};

