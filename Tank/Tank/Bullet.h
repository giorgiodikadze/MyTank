#pragma once
#include "moveableblock.h"
class Bullet :
	public MoveableBlock
{
public:
	Bullet(int _real_x, int _real_y, short _direction, short _speed=10, short _type=64);
	~Bullet(void);

	void Draw(HDC &hdc);

	void Move(short direction);

	static const int BULLET_WIDTH = 15;
};

