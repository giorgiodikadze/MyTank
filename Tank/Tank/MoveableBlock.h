#pragma once
#include "block.h"
class MoveableBlock :
	public Block
{
public:
	MoveableBlock(short _x, short _y, short _type, short speed=2, short _direction=UP);
	~MoveableBlock(void);

	virtual void UpdataDataFromX(int _real_x);
	virtual void UpdataDataFromY(int _real_y);

	short speed, direction;
	int top,bottom,left,right;
	static const short DOWN=0, LEFT=1, UP=2, RIGHT=3;
};

