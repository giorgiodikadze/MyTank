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
	if(state > 0) state--;
}