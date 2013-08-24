#pragma once
class Block
{
public:
	Block(short _x, short _y,short _type , bool _throughable = false);
	virtual ~Block(void);
	virtual void Draw(HDC &hdc);
	virtual void TransparentPNG(CImage *png);

	short type,x,y;
	int real_x,real_y;
	CImage blockImage;
	bool throughable;
	static short const BLOCK_WIDTH = 40;
};

