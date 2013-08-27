#pragma once
#include "MoveableBlock.h"
#include "MapBlock.h"

class GTank;

class Bullet
	:public MoveableBlock
{
public:
	Bullet(int _real_x, int _real_y, short _direction, short _speed=5, short _type=64);
	~Bullet(void);

	void Draw(HDC &hdc);

	void Move();

	bool hitMap();

	bool bullet_enable;
	static const int BULLET_WIDTH = 8;
};




