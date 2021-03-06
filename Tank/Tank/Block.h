#pragma once
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

class Block
{
public:
	Block(short _x, short _y,short _type , bool _throughable = false);
	virtual ~Block(void);
	static void TransparentPNG(CImage *png);
	virtual void Draw(HDC &hdc);
	virtual void Explode();

	short type,x,y;
	int real_x,real_y;
	CImage blockImage;
	bool throughable;
	static short const BLOCK_WIDTH = 40;
};

