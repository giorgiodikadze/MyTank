#pragma once
#include "block.h"
class MoveableBlock :
	public Block
{
public:
	MoveableBlock(int real_x, int real_y, short _type, short speed=5, short _direction=UP);
	~MoveableBlock(void);

	virtual void UpdataDataFromX(int _real_x);
	virtual void UpdataDataFromY(int _real_y);

	short speed, direction;
	int top,bottom,left,right;
	static const short DOWN=0, LEFT=1, UP=2, RIGHT=3;
};

