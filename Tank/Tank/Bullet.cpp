#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(int _real_x, int _real_y, short _direction,  short _speed, short _type)
	:MoveableBlock(_real_x, _real_y, _type, _speed, _direction)
{
	blockImage.Load(_T(".\\res\\image\\bullet.png"));
	TransparentPNG(&blockImage);
	right = left + blockImage.GetWidth()/4;
	bottom = top + blockImage.GetHeight();
}


Bullet::~Bullet(void)
{
}

void Bullet::Move(short _direction)
{
	direction = _direction;
	switch (direction)
	{
	case DOWN:
		UpdataDataFromY(speed);
		break;
	case LEFT:
		UpdataDataFromX(-1 * speed);
		break;
	case UP:
		UpdataDataFromY(-1 * speed);
		break;
	case RIGHT:
		UpdataDataFromX(speed);
		break;
	default:
		break;
	}
}

void Bullet::Draw(HDC &hdc)
{
	blockImage.Draw(hdc, real_x, real_y, BULLET_WIDTH, BULLET_WIDTH, direction * blockImage.GetWidth()/4, 
		0, blockImage.GetWidth()/4, blockImage.GetHeight());
}
