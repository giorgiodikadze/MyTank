#include "stdafx.h"
#include "Block.h"


Block::Block(short _x, short _y, short _type , bool _throughable):x(_x), y(_y), type(_type), throughable(_throughable)
{
	real_x = BLOCK_WIDTH * x;
	real_y = BLOCK_WIDTH * y;
}


Block::~Block(void)
{
}

void Block::Draw(HDC &hdc)
{
}

void Block::TransparentPNG(CImage *png)
{
	for(int i = 0; i <png->GetWidth(); i++)
	{
		for(int j = 0; j <png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(png->GetPixelAddress(i , j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}