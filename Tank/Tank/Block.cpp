/*
#	Copyright © 2013 Shaw 499012219@qq.com
#   This file is part of Tank.

#    Tank is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.

#    Tank is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

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
void Block::Explode()
{}