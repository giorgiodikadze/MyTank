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
