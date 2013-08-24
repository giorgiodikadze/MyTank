#pragma once
#include "block.h"
class MapBlock :
	public Block
{
public:
	MapBlock(short _x, short _y, short _type);
	~MapBlock(void);

	void Draw(HDC &hdc);

	short state, AllState;
};

