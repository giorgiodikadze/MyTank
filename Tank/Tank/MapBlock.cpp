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
#include "MapBlock.h"


MapBlock::MapBlock(short _x, short _y, short _type):Block(_x, _y, _type), state(0)
{
	if(type == 1) throughable = true;
	if(type == 3) state = 5;
	else if(type == 5) state = 1;
	AllState = state + 1;
 	TCHAR imageName[30];
	wsprintf(imageName,_T(".\\res\\image\\M%d.png"),type);
	blockImage.Load(imageName);
	TransparentPNG(&blockImage);
}


MapBlock::~MapBlock(void)
{
}

void MapBlock::Draw(HDC &hdc)
{
	blockImage.Draw(hdc, real_x, real_y, BLOCK_WIDTH, BLOCK_WIDTH, state * blockImage.GetWidth()/AllState, 
		0, blockImage.GetWidth()/AllState, blockImage.GetHeight());
}

void MapBlock::Explode()
{
	if(type == 5) PlaySound(_T(".\\res\\wav\\bang.wav"),NULL,SND_FILENAME | SND_ASYNC);
	if(state > 0) state--;
}