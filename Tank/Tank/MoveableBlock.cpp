#include "stdafx.h"
#include "MoveableBlock.h"


MoveableBlock::MoveableBlock(short _x, short _y, short _type, short _speed, short _direction)
	:Block(_x, _y, _type),speed(_speed),direction(_direction)
{
}

MoveableBlock::~MoveableBlock(void)
{
}

void MoveableBlock::UpdataDataFromX(int delta_real_x)
{
	real_x += delta_real_x;
	left += delta_real_x;
	right += delta_real_x;
	x = real_x / BLOCK_WIDTH;
}

void MoveableBlock::UpdataDataFromY(int delta_real_y)
{
	real_y += delta_real_y;
	top += delta_real_y;
	bottom += delta_real_y;
	y = real_y / BLOCK_WIDTH;
}
